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

using namespace ns3;

int main(int argc, char *argv[])
{
    Filter filter;
    SourceIpAddress* srcIp = new SourceIpAddress("10.1.1.1");
    SourceMask* srcMask = new SourceMask("10.1.1.0", "/24");
    SourcePortNumber* srcPort = new SourcePortNumber(2048);
    DestinationIpAddress* destIp = new DestinationIpAddress("192.168.1.1");
    DestinationMask* destMask = new DestinationMask("192.168.1.0", "255.255.255.0");
    DestinationPortNumber* destPort = new DestinationPortNumber(1024);
    ProtocolNumber* protocol = new ProtocolNumber(17);

    filter.AddElement(srcIp);
    filter.AddElement(srcMask);
    filter.AddElement(srcPort);
    filter.AddElement(destIp);
    filter.AddElement(destMask);
    filter.AddElement(destPort);
    filter.AddElement(protocol);

    // Create a packet with source IP 10.1.1.1
    Ptr<Packet> packet = Create<Packet>();

    UdpHeader udpHeader;
    udpHeader.SetSourcePort(2048);
    udpHeader.SetDestinationPort(1024);
    packet->AddHeader(udpHeader);

    
    Ipv4Header ipv4Header;
    ipv4Header.SetSource(Ipv4Address("10.1.1.1"));
    ipv4Header.SetDestination(Ipv4Address("192.168.1.1"));
    ipv4Header.SetProtocol(17);
    packet->AddHeader(ipv4Header);

    // Expect the filter to match
    if (filter.Match(packet))
    {
        std::cout << "Filter matched\n";
    }
    else
    {
        std::cout<<"Filter did not match\n";
    }

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}