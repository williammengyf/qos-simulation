#include "spq.h"
#include "traffic-class.h"

namespace ns3
{

/**
 * Constructor.
*/
Spq::Spq()
    : DiffServ()
{
}

/**
 * Destructor.
*/
Spq::~Spq()
{
}

/**
 * Determines which traffic class to be served and retrieves a packet from it.
 * 
 * \returns Pointer to the packet.
*/
Ptr<Packet>
Spq::Schedule()
{
    uint32_t maxPriorityLevel = 0;
    TrafficClass* classToServe = nullptr;
    for (TrafficClass* trafficClass : q_class)
    {
        trafficClass->SetActive(false);
        if (trafficClass->Peek() && trafficClass->GetPriorityLevel() > maxPriorityLevel)
        {
            classToServe = trafficClass;
            maxPriorityLevel = trafficClass->GetPriorityLevel();
        }
    }

    if (!classToServe)
    {
        return nullptr;
    }

    classToServe->SetActive(true);
    Ptr<Packet> p = classToServe->Dequeue();

    return p;
}

/**
 * Determines which traffic class to be served next.
 * 
 * \returns Index of the traffic class.
*/
uint32_t
Spq::NextClass() const
{
    uint32_t maxPriorityLevel = 0;
    uint32_t nextClass = q_class.size();
    uint32_t index = 0;
    for (TrafficClass* trafficClass : q_class)
    {
        if (trafficClass->Peek() && trafficClass->GetPriorityLevel() > maxPriorityLevel)
        {
            nextClass = index;
            maxPriorityLevel = trafficClass->GetPriorityLevel();
        }

        index++;
    }

    return nextClass;
}

} // namespace ns3
