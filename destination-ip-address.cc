#include "destination-ip-address.h"

#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

DestinationIpAddress::DestinationIpAddress()
    : m_address()
{
}

DestinationIpAddress::DestinationIpAddress(const char* address)
    : m_address(address)
{
}

DestinationIpAddress::~DestinationIpAddress()
{
}

bool
DestinationIpAddress::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    Ipv4Address destIpAddress = ipv4Header.GetDestination();
    return m_address == destIpAddress;
}

}
