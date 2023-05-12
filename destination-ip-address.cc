#include "destination-ip-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
DestinationIpAddress::DestinationIpAddress()
    : m_address()
{
}

/**
 * Constructor.
 * 
 * \param address Expected destination Ip address.
*/
DestinationIpAddress::DestinationIpAddress(const char* address)
    : m_address(address)
{
}

/**
 * Destructor.
*/
DestinationIpAddress::~DestinationIpAddress()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
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

} // namespace ns3
