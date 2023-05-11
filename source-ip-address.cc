#include "source-ip-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

SourceIpAddress::SourceIpAddress()
    : m_address()
{
}

SourceIpAddress::SourceIpAddress(const char* address)
    : m_address(address)
{
}

SourceIpAddress::~SourceIpAddress()
{
}

bool
SourceIpAddress::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    Ipv4Address srcIpAddress = ipv4Header.GetSource();
    return m_address == srcIpAddress;
}

}
