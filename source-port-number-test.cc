#include "filter-element.h"
#include "source-port-number.h"
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

    SourcePortNumber filter(2048);

    // Create a packet with source IP 10.1.1.1
    Ptr<Packet> packet = Create<Packet>();

    UdpHeader tcpHeader;
    tcpHeader.SetSourcePort(2048);
    packet->AddHeader(tcpHeader);

    
    Ipv4Header ipv4Header;
    ipv4Header.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header.SetProtocol(17);
    packet->AddHeader(ipv4Header);

    PppHeader pppHeader;
    packet->AddHeader(pppHeader);

    // Expect the filter to match
    if (filter.Match(packet))
    {
        std::cout << "Filter matched\n";
    }
    else
    {
        std::cout<<"Filter did not match\n";
    }

    // Create a packet with source IP 10.1.1.2
    Ptr<Packet> packet2 = Create<Packet>();

    UdpHeader udpHeader;
    udpHeader.SetSourcePort(2048);
    packet2->AddHeader(udpHeader);

    Ipv4Header ipv4Header2;
    ipv4Header2.SetSource(Ipv4Address("10.1.1.2"));
    ipv4Header2.SetProtocol(6);
    packet2->AddHeader(ipv4Header2);

    // Expect the filter to not match
    if (filter.Match(packet2))
    {
        std::cout<<"Filter matched\n";
    }
    else
    {
        std::cout<<"Filter did not match\n";
    }

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
