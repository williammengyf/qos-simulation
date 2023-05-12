#include "diff-serv.h"
#include "destination-ip-address.h"
#include "destination-mask.h"
#include "destination-port-number.h"
#include "filter-element.h"
#include "filter.h"
#include "protocol-number.h"
#include "source-ip-address.h"
#include "source-mask.h"
#include "source-port-number.h"
#include "ns3/ipv4-header.h"
#include "ns3/packet.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

namespace ns3
{

/**
 * Constructor.
*/
DiffServ::DiffServ()
    : Queue<Packet>()
{
}

/**
 * Destructor.
*/
DiffServ::~DiffServ()
{
    for (TrafficClass* trafficClass : q_class)
    {
        delete trafficClass;
    }
}

/**
 * Loads config from file.
 * 
 * \param filename Config file.
 * \returns True if succeeded.
*/
bool
DiffServ::LoadConfig(const char* filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        return false;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    if (file.bad())
    {
        return false;
    }

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<> *rootNode = doc.first_node("root");
    if (!rootNode)
    {
        return false;
    }

    rapidxml::xml_node<> *numberOfQueuesNode = rootNode->first_node("numberOfQueues");
    if (!numberOfQueuesNode)
    {
        return false;
    }

    rapidxml::xml_node<> *queuesNode = rootNode->first_node("queues");
    for (rapidxml::xml_node<> *queueNode = queuesNode->first_node("queue");
         queueNode;
         queueNode = queueNode->next_sibling())
    {
        TrafficClass* queue = new TrafficClass();
        
        for (rapidxml::xml_node<> *attribute = queueNode->first_node();
             attribute;
             attribute = attribute->next_sibling())
        {
            std::string attributeName(attribute->name());

            if (attributeName == "maxPackets")
            {
                std::string attributeValue(attribute->value());
                uint32_t maxPackets = static_cast<uint32_t>(std::stoul(attributeValue));
                queue->SetMaxPackets(maxPackets);
            }
            else if (attributeName == "priorityLevel")
            {
                std::string attributeValue(attribute->value());
                uint32_t priorityLevel = static_cast<uint32_t>(std::stoul(attributeValue));
                queue->SetPriorityLevel(priorityLevel);
            }
            else if (attributeName == "weight")
            {
                std::string attributeValue(attribute->value());
                uint32_t weight = static_cast<uint32_t>(std::stoul(attributeValue));
                queue->SetWeight(weight);
            }
            else if (attributeName == "isDefault")
            {
                std::string attributeValue(attribute->value());
                std::transform(attributeValue.begin(),
                               attributeValue.end(),
                               attributeValue.begin(),
                               [](unsigned char c){ return std::tolower(c); });
                bool isDefault = (attributeValue == "true");
                queue->SetDefault(isDefault);
            }
            else if (attributeName == "filters")
            {
                for (rapidxml::xml_node<> *filterNode = attribute->first_node("filter");
                     filterNode;
                     filterNode = filterNode->next_sibling())
                {
                    Filter* filter = new Filter();

                    rapidxml::xml_node<> *filterElementsNode = filterNode->first_node("filterElements");
                    for (rapidxml::xml_node<> *filterElement = filterElementsNode->first_node();
                         filterElement;
                         filterElement = filterElement->next_sibling())
                    {
                        std::string elementName(filterElement->name());

                        if (elementName == "sourceIpAddress")
                        {
                            std::string address(filterElement->value());
                            SourceIpAddress *srcIp = new SourceIpAddress(address.c_str());
                            filter->AddElement(srcIp);
                        }
                        else if (elementName == "destinationIpAddress")
                        {
                            std::string address(filterElement->value());
                            DestinationIpAddress *destIp = new DestinationIpAddress(address.c_str());
                            filter->AddElement(destIp);
                        }
                        else if (elementName == "sourcePortNumber")
                        {
                            std::string portStr(filterElement->value());
                            int portNum = std::stoi(portStr);
                            if (portNum < 0 || portNum > UINT16_MAX)
                            {
                                return false;
                            }
                            SourcePortNumber *srcPort = new SourcePortNumber(static_cast<uint16_t>(portNum));
                            filter->AddElement(srcPort);
                        }
                        else if (elementName == "destinationPortNumber")
                        {
                            std::string portStr(filterElement->value());
                            int portNum = std::stoi(portStr);
                            if (portNum < 0 || portNum > UINT16_MAX)
                            {
                                return false;
                            }
                            DestinationPortNumber *destPort = new DestinationPortNumber(static_cast<uint16_t>(portNum));
                            filter->AddElement(destPort);
                        }
                        else if (elementName == "protocolNumber")
                        {
                            std::string protocolStr(filterElement->value());
                            int protocolNum = std::stoi(protocolStr);
                            if (protocolNum < 0 || protocolNum > UINT8_MAX)
                            {
                                return false;
                            }
                            ProtocolNumber *protocol = new ProtocolNumber(static_cast<uint8_t>(protocolNum));
                            filter->AddElement(protocol);
                        }
                        else if (elementName == "sourceMask")
                        {
                            std::string address, mask;
                            for (rapidxml::xml_node<> *maskValue = filterElement->first_node();
                                 maskValue;
                                 maskValue = maskValue->next_sibling())
                            {
                                std::string valueName(maskValue->name());

                                if (valueName == "address")
                                {
                                    address = std::string(maskValue->value());
                                }
                                else if (valueName == "mask")
                                {
                                    mask = std::string(maskValue->value());
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            SourceMask *srcMask = new SourceMask(address.c_str(), mask.c_str());
                            filter->AddElement(srcMask);
                        }
                        else if (elementName == "destinationMask")
                        {
                            std::string address, mask;
                            for (rapidxml::xml_node<> *maskValue = filterElement->first_node();
                                 maskValue;
                                 maskValue = maskValue->next_sibling())
                            {
                                std::string valueName(maskValue->name());

                                if (valueName == "address")
                                {
                                    address = std::string(maskValue->value());
                                }
                                else if (valueName == "mask")
                                {
                                    mask = std::string(maskValue->value());
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            DestinationMask *destMask = new DestinationMask(address.c_str(), mask.c_str());
                            filter->AddElement(destMask);
                        }
                        else
                        {
                            return false;
                        }
                    }

                    queue->m_filters.push_back(filter);
                }
            }
            else
            {
                return false;
            }
        }

        AddClass(queue);
    }

    return true;
}

/**
 * Places a packet into the queue.
 * 
 * \param p Pointer to the packet.
 * \returns True if succeeded.
*/
bool
DiffServ::Enqueue(Ptr<Packet> p)
{
    return DoEnqueue(p);
}

/**
 * Removes a packet from the queue.
 * 
 * \returns Pointer to the packet.
*/
Ptr<Packet>
DiffServ::Dequeue()
{
    Ptr<Packet> p = DoDequeue();
    return p;
}

/**
 * Removes and drops a packet from the queue.
 * 
 * \returns Pointer to the packet. 
*/
Ptr<Packet>
DiffServ::Remove()
{
    Ptr<Packet> p = DoRemove();
    return p;
}

/**
 * Retrieves, but does not remove a packet from the queue.
 * 
 * \returns Poniter to the packet.
*/
Ptr<const Packet>
DiffServ::Peek() const
{
    return DoPeek();
}

/**
 * Adds a traffic class to the queue.
 * 
 * \param trafficClass Pointer to the traffic class.
*/
void
DiffServ::AddClass(TrafficClass* trafficClass)
{
    q_class.push_back(trafficClass);
}

/**
 * Determines which traffic class a packet will be placed.
 * 
 * \param p Pointer to the packet.
 * \returns Index of the traffic class.
*/
uint32_t
DiffServ::Classify(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();
    PppHeader ppph;
    Ipv4Header iph;
    UdpHeader udph;
    copy->RemoveHeader(ppph);
    copy->RemoveHeader(iph);
    copy->RemoveHeader(udph);
    uint32_t index = 0;
    // If there is no matched or default traffic class, drop the packet.
    uint32_t defaultIndex = q_class.size();
    for (TrafficClass* trafficClass : q_class)
    {
        if (trafficClass->Match(p))
        {
            return index;
        }

        if (trafficClass->IsDefault())
        {
            defaultIndex = index;
        }

        index++;
    }
    return defaultIndex;
}

/**
 * Pushes a packet to the queue.
 * 
 * \param p Pointer to the packet.
 * \returns True if succeeded.
*/
bool
DiffServ::DoEnqueue(Ptr<Packet> p)
{
    uint32_t index = Classify(p);
    if (index >= q_class.size())
    {
        DropBeforeEnqueue(p);
        return false;
    }

    bool success = q_class[index]->Enqueue(p);
    if (!success)
    {
        DropBeforeEnqueue(p);
    }

    return success;
}

/**
 * Pulls a packet from the queue.
 * 
 * \returns Pointer to the packet.
*/
Ptr<Packet>
DiffServ::DoDequeue()
{
    Ptr<Packet> p = Schedule();
    return p;
}

/**
 * Drops a packet from the queue.
 * 
 * \returns Pointer to the packet.
*/
Ptr<Packet>
DiffServ::DoRemove()
{
    Ptr<Packet> p = Schedule();
    if (p)
    {
        DropAfterDequeue(p);
    }

    return p;
}

/**
 * Peeks a packet in the queue.
 * 
 * \returns Pointer to the packet.
*/
Ptr<const Packet>
DiffServ::DoPeek() const
{
    uint32_t index = NextClass();
    if (index >= q_class.size())
    {
        return nullptr;
    }

    return q_class[index]->Peek();
}

} // namespace ns3
