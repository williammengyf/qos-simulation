#include "spq.h"
#include "diff-serv.h"
#include "filter.h"
#include "filter-element.h"
#include "source-ip-address.h"
#include "source-mask.h"
#include "source-port-number.h"
#include "destination-ip-address.h"
#include "destination-mask.h"
#include "destination-port-number.h"
#include "protocol-number.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/packet.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"

using namespace ns3;

int main(int argc, char *argv[])
{
    TrafficClass* class1 = new TrafficClass();
    Filter* filter1 = new Filter();
    SourceIpAddress* srcIp1 = new SourceIpAddress("10.1.1.1");
    SourceMask* srcMask1 = new SourceMask("10.1.1.0", "/24");
    SourcePortNumber* srcPort1 = new SourcePortNumber(2048);
    DestinationIpAddress* destIp1 = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask1 = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort1 = new DestinationPortNumber(1024);
    ProtocolNumber* protocol1 = new ProtocolNumber(17);

    filter1->AddElement(srcIp1);
    filter1->AddElement(srcMask1);
    filter1->AddElement(srcPort1);
    filter1->AddElement(destIp1);
    filter1->AddElement(destMask1);
    filter1->AddElement(destPort1);
    filter1->AddElement(protocol1);
    class1->m_filters.push_back(filter1);
    class1->SetMaxPackets(10);
    class1->SetPriorityLevel(2);
    class1->SetDefault(false);

    TrafficClass* class2 = new TrafficClass();
    Filter* filter2 = new Filter();
    SourceIpAddress* srcIp2 = new SourceIpAddress("10.1.2.1");
    SourceMask* srcMask2 = new SourceMask("10.1.2.0", "255.255.255.0");
    SourcePortNumber* srcPort2 = new SourcePortNumber(4096);
    DestinationIpAddress* destIp2 = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask2 = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort2 = new DestinationPortNumber(8192);
    ProtocolNumber* protocol2 = new ProtocolNumber(17);

    filter2->AddElement(srcIp2);
    filter2->AddElement(srcMask2);
    filter2->AddElement(srcPort2);
    filter2->AddElement(destIp2);
    filter2->AddElement(destMask2);
    filter2->AddElement(destPort2);
    filter2->AddElement(protocol2);
    class2->m_filters.push_back(filter2);
    class2->SetMaxPackets(10);
    class2->SetPriorityLevel(1);
    class2->SetDefault(true);

    Spq* queue = new Spq();
    queue->AddClass(class1);
    queue->AddClass(class2);

    // Create a packet with source IP 10.1.1.1
    Ptr<Packet> packet1 = Create<Packet>();

    UdpHeader udpHeader1;
    udpHeader1.SetSourcePort(4096);
    udpHeader1.SetDestinationPort(1024);
    packet1->AddHeader(udpHeader1);

    
    Ipv4Header ipv4Header1;
    ipv4Header1.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header1.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header1.SetProtocol(17);
    packet1->AddHeader(ipv4Header1);

    PppHeader pppHeader1;
    packet1->AddHeader(pppHeader1);

    Ptr<Packet> packet2 = Create<Packet>();

    UdpHeader udpHeader2;
    udpHeader2.SetSourcePort(4096);
    udpHeader2.SetDestinationPort(8192);
    packet2->AddHeader(udpHeader2);

    
    Ipv4Header ipv4Header2;
    ipv4Header2.SetSource(Ipv4Address("10.1.2.1"));
    ipv4Header2.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header2.SetProtocol(17);
    packet2->AddHeader(ipv4Header2);

    PppHeader pppHeader2;
    packet2->AddHeader(pppHeader2);

    Ptr<Packet> packet3 = Create<Packet>();

    UdpHeader udpHeader3;
    udpHeader3.SetSourcePort(2048);
    udpHeader3.SetDestinationPort(1024);
    packet3->AddHeader(udpHeader3);

    
    Ipv4Header ipv4Header3;
    ipv4Header3.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header3.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header3.SetProtocol(17);
    packet3->AddHeader(ipv4Header3);

    PppHeader pppHeader3;
    packet3->AddHeader(pppHeader3);

    queue->Enqueue(packet1);
    queue->Enqueue(packet2);
    queue->Enqueue(packet3);

    Ptr<Packet> p1 = queue->Dequeue();
    Ptr<Packet> p2 = queue->Remove();
    Ptr<const Packet> p3 = queue->Peek();

    if (filter1->Match(p1))
    {
        std::cout << "Packet from queue 1\n";
    }
    else
    {
        std::cout<<"Packet from queue 2\n";
    }

    PppHeader ppph1;
    Ipv4Header iph1;
    UdpHeader udph1;
    p1->RemoveHeader(ppph1);
    p1->RemoveHeader(iph1);
    p1->RemoveHeader(udph1);
    std::cout<<iph1.GetSource()<<':'<<udph1.GetSourcePort()<<'\n';
    std::cout<<iph1.GetDestination()<<':'<<udph1.GetDestinationPort()<<'\n';

    if (filter1->Match(p2))
    {
        std::cout << "Packet from queue 1\n";
    }
    else
    {
        std::cout<<"Packet from queue 2\n";
    }

    PppHeader ppph2;
    Ipv4Header iph2;
    UdpHeader udph2;
    p2->RemoveHeader(ppph2);
    p2->RemoveHeader(iph2);
    p2->RemoveHeader(udph2);
    std::cout<<iph2.GetSource()<<':'<<udph2.GetSourcePort()<<'\n';
    std::cout<<iph2.GetDestination()<<':'<<udph2.GetDestinationPort()<<'\n';

    Ptr<Packet> copy = p3->Copy();
    PppHeader ppph3;
    Ipv4Header iph3;
    UdpHeader udph3;
    copy->RemoveHeader(ppph3);
    copy->RemoveHeader(iph3);
    copy->RemoveHeader(udph3);
    std::cout<<iph3.GetSource()<<':'<<udph3.GetSourcePort()<<'\n';
    std::cout<<iph3.GetDestination()<<':'<<udph3.GetDestinationPort()<<'\n';

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}