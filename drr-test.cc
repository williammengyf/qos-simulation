#include "drr.h"
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
#include "ns3/udp-header.h"

#include <cstdint>
#include <cstring>

using namespace ns3;

uint8_t*
zero_bytes(std::size_t size)
{
    uint8_t* buffer = new uint8_t[size];
    std::memset(buffer, 0, size);
    return buffer;
}

int
main(int argc, char *argv[])
{
    TrafficClass* class1 = new TrafficClass();
    Filter* filter1 = new Filter();
    SourceIpAddress* srcIp1 = new SourceIpAddress("10.1.1.1");
    SourceMask* srcMask1 = new SourceMask("10.1.1.0", "/24");
    SourcePortNumber* srcPort1 = new SourcePortNumber(1024);
    DestinationIpAddress* destIp1 = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask1 = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort1 = new DestinationPortNumber(2048);
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
    class1->SetWeight(600);
    class1->SetDefault(true);

    TrafficClass* class2 = new TrafficClass();
    Filter* filter2 = new Filter();
    SourceIpAddress* srcIp2 = new SourceIpAddress("10.1.2.1");
    SourceMask* srcMask2 = new SourceMask("10.1.2.0", "255.255.255.0");
    SourcePortNumber* srcPort2 = new SourcePortNumber(2048);
    DestinationIpAddress* destIp2 = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask2 = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort2 = new DestinationPortNumber(4096);
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
    class2->SetWeight(400);
    class2->SetDefault(false);

    TrafficClass* class3 = new TrafficClass();
    Filter* filter3 = new Filter();
    SourceIpAddress* srcIp3 = new SourceIpAddress("10.1.3.1");
    SourceMask* srcMask3 = new SourceMask("10.1.3.0", "255.255.255.0");
    SourcePortNumber* srcPort3 = new SourcePortNumber(4096);
    DestinationIpAddress* destIp3 = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask3 = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort3 = new DestinationPortNumber(8192);
    ProtocolNumber* protocol3 = new ProtocolNumber(17);

    filter3->AddElement(srcIp3);
    filter3->AddElement(srcMask3);
    filter3->AddElement(srcPort3);
    filter3->AddElement(destIp3);
    filter3->AddElement(destMask3);
    filter3->AddElement(destPort3);
    filter3->AddElement(protocol3);
    class3->m_filters.push_back(filter3);
    class3->SetMaxPackets(10);
    class3->SetWeight(200);
    class3->SetDefault(false);

    Drr* queue = new Drr();
    queue->AddClass(class1);
    queue->AddClass(class2);
    queue->AddClass(class3);

    uint8_t* buffer1 = zero_bytes(200);
    Ptr<Packet> packet1 = Create<Packet>(buffer1, 200);
    delete[] buffer1;

    UdpHeader udpHeader1;
    udpHeader1.SetSourcePort(1024);
    udpHeader1.SetDestinationPort(2048);
    packet1->AddHeader(udpHeader1);

    Ipv4Header ipv4Header1;
    ipv4Header1.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header1.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header1.SetProtocol(17);
    packet1->AddHeader(ipv4Header1);

    PppHeader pppHeader1;
    packet1->AddHeader(pppHeader1);

    uint8_t* buffer2 = zero_bytes(300);
    Ptr<Packet> packet2 = Create<Packet>(buffer2, 300);
    delete[] buffer2;

    UdpHeader udpHeader2;
    udpHeader2.SetSourcePort(1024);
    udpHeader2.SetDestinationPort(2048);
    packet2->AddHeader(udpHeader2);

    Ipv4Header ipv4Header2;
    ipv4Header2.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header2.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header2.SetProtocol(17);
    packet2->AddHeader(ipv4Header2);

    PppHeader pppHeader2;
    packet2->AddHeader(pppHeader2);

    uint8_t* buffer3 = zero_bytes(200);
    Ptr<Packet> packet3 = Create<Packet>(buffer3, 200);
    delete[] buffer3;

    UdpHeader udpHeader3;
    udpHeader3.SetSourcePort(1024);
    udpHeader3.SetDestinationPort(1024);
    packet3->AddHeader(udpHeader3);

    Ipv4Header ipv4Header3;
    ipv4Header3.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header3.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header3.SetProtocol(17);
    packet3->AddHeader(ipv4Header3);

    PppHeader pppHeader3;
    packet3->AddHeader(pppHeader3);

    uint8_t* buffer4 = zero_bytes(300);
    Ptr<Packet> packet4 = Create<Packet>(buffer4, 300);
    delete[] buffer4;

    UdpHeader udpHeader4;
    udpHeader4.SetSourcePort(2048);
    udpHeader4.SetDestinationPort(4096);
    packet4->AddHeader(udpHeader4);

    Ipv4Header ipv4Header4;
    ipv4Header4.SetSource(Ipv4Address("10.1.2.1"));
    ipv4Header4.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header4.SetProtocol(17);
    packet4->AddHeader(ipv4Header4);

    PppHeader pppHeader4;
    packet4->AddHeader(pppHeader4);

    uint8_t* buffer5 = zero_bytes(300);
    Ptr<Packet> packet5 = Create<Packet>(buffer5, 300);
    delete[] buffer5;

    UdpHeader udpHeader5;
    udpHeader5.SetSourcePort(2048);
    udpHeader5.SetDestinationPort(4096);
    packet5->AddHeader(udpHeader5);

    Ipv4Header ipv4Header5;
    ipv4Header5.SetSource(Ipv4Address("10.1.2.1"));
    ipv4Header5.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header5.SetProtocol(17);
    packet5->AddHeader(ipv4Header5);

    PppHeader pppHeader5;
    packet5->AddHeader(pppHeader5);

    uint8_t* buffer6 = zero_bytes(100);
    Ptr<Packet> packet6 = Create<Packet>(buffer6, 100);
    delete[] buffer6;

    UdpHeader udpHeader6;
    udpHeader6.SetSourcePort(4096);
    udpHeader6.SetDestinationPort(8192);
    packet6->AddHeader(udpHeader6);

    Ipv4Header ipv4Header6;
    ipv4Header6.SetSource(Ipv4Address("10.1.3.1"));
    ipv4Header6.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header6.SetProtocol(17);
    packet6->AddHeader(ipv4Header6);

    PppHeader pppHeader6;
    packet6->AddHeader(pppHeader6);

    uint8_t* buffer7 = zero_bytes(200);
    Ptr<Packet> packet7 = Create<Packet>(buffer7, 200);
    delete[] buffer7;

    UdpHeader udpHeader7;
    udpHeader7.SetSourcePort(4096);
    udpHeader7.SetDestinationPort(8192);
    packet7->AddHeader(udpHeader7);

    Ipv4Header ipv4Header7;
    ipv4Header7.SetSource(Ipv4Address("10.1.3.1"));
    ipv4Header7.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header7.SetProtocol(17);
    packet7->AddHeader(ipv4Header7);

    PppHeader pppHeader7;
    packet7->AddHeader(pppHeader7);

    queue->Enqueue(packet1);
    queue->Enqueue(packet2);
    queue->Enqueue(packet3);
    queue->Enqueue(packet4);
    queue->Enqueue(packet5);
    queue->Enqueue(packet6);
    queue->Enqueue(packet7);

    Ptr<Packet> p1 = queue->Dequeue();
    Ptr<Packet> p2 = queue->Remove();
    Ptr<Packet> p3 = queue->Dequeue();
    Ptr<Packet> p4 = queue->Remove();
    Ptr<Packet> p5 = queue->Dequeue();
    Ptr<Packet> p6 = queue->Remove();
    Ptr<const Packet> p7 = queue->Peek();

    if (filter3->Match(p1))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p1))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph1;
    Ipv4Header iph1;
    UdpHeader udph1;
    p1->RemoveHeader(ppph1);
    p1->RemoveHeader(iph1);
    p1->RemoveHeader(udph1);
    std::cout<<iph1.GetSource()<<':'<<udph1.GetSourcePort()<<'\n';
    std::cout<<iph1.GetDestination()<<':'<<udph1.GetDestinationPort()<<'\n';
    std::cout<<p1->GetSize()<<'\n';

    if (filter3->Match(p2))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p2))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph2;
    Ipv4Header iph2;
    UdpHeader udph2;
    p2->RemoveHeader(ppph2);
    p2->RemoveHeader(iph2);
    p2->RemoveHeader(udph2);
    std::cout<<iph2.GetSource()<<':'<<udph2.GetSourcePort()<<'\n';
    std::cout<<iph2.GetDestination()<<':'<<udph2.GetDestinationPort()<<'\n';
    std::cout<<p2->GetSize()<<'\n';

    if (filter3->Match(p3))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p3))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph3;
    Ipv4Header iph3;
    UdpHeader udph3;
    p3->RemoveHeader(ppph3);
    p3->RemoveHeader(iph3);
    p3->RemoveHeader(udph3);
    std::cout<<iph3.GetSource()<<':'<<udph3.GetSourcePort()<<'\n';
    std::cout<<iph3.GetDestination()<<':'<<udph3.GetDestinationPort()<<'\n';
    std::cout<<p3->GetSize()<<'\n';

    if (filter3->Match(p4))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p4))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph4;
    Ipv4Header iph4;
    UdpHeader udph4;
    p4->RemoveHeader(ppph4);
    p4->RemoveHeader(iph4);
    p4->RemoveHeader(udph4);
    std::cout<<iph4.GetSource()<<':'<<udph4.GetSourcePort()<<'\n';
    std::cout<<iph4.GetDestination()<<':'<<udph4.GetDestinationPort()<<'\n';
    std::cout<<p4->GetSize()<<'\n';

    if (filter3->Match(p5))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p5))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph5;
    Ipv4Header iph5;
    UdpHeader udph5;
    p5->RemoveHeader(ppph5);
    p5->RemoveHeader(iph5);
    p5->RemoveHeader(udph5);
    std::cout<<iph5.GetSource()<<':'<<udph5.GetSourcePort()<<'\n';
    std::cout<<iph5.GetDestination()<<':'<<udph5.GetDestinationPort()<<'\n';
    std::cout<<p5->GetSize()<<'\n';

    if (filter3->Match(p6))
    {
        std::cout << "Packet from queue 3\n";
    }
    else if (filter2->Match(p6))
    {
        std::cout<<"Packet from queue 2\n";
    }
    else
    {
        std::cout<<"Packet from queue 1\n";
    }

    PppHeader ppph6;
    Ipv4Header iph6;
    UdpHeader udph6;
    p6->RemoveHeader(ppph6);
    p6->RemoveHeader(iph6);
    p6->RemoveHeader(udph6);
    std::cout<<iph6.GetSource()<<':'<<udph6.GetSourcePort()<<'\n';
    std::cout<<iph6.GetDestination()<<':'<<udph6.GetDestinationPort()<<'\n';
    std::cout<<p6->GetSize()<<'\n';

    Ptr<Packet> copy = p7->Copy();
    PppHeader ppph7;
    Ipv4Header iph7;
    UdpHeader udph7;
    copy->RemoveHeader(ppph7);
    copy->RemoveHeader(iph7);
    copy->RemoveHeader(udph7);
    std::cout<<iph7.GetSource()<<':'<<udph7.GetSourcePort()<<'\n';
    std::cout<<iph7.GetDestination()<<':'<<udph7.GetDestinationPort()<<'\n';
    std::cout<<copy->GetSize()<<'\n';

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
