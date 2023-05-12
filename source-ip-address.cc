#include "source-ip-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
SourceIpAddress::SourceIpAddress()
    : m_address()
{
}

/**
 * Constructor.
 * 
 * \param address Expected source Ip address.
*/
SourceIpAddress::SourceIpAddress(const char* address)
    : m_address(address)
{
}

/**
 * Destructor.
*/
SourceIpAddress::~SourceIpAddress()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
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

} // namespace ns3
