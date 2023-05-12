#include "destination-mask.h"

#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
DestinationMask::DestinationMask()
    : m_address(),
      m_mask()
{
}

/**
 * Constructor.
 * 
 * \param address Expected destination IP address.
 * \param mask Expected destination IP mask.
*/
DestinationMask::DestinationMask(const char* address, const char* mask)
    : m_address(address),
      m_mask(mask)
{
}

/**
 * Destructor.
*/
DestinationMask::~DestinationMask()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
bool
DestinationMask::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    Ipv4Address destIpAddress = ipv4Header.GetDestination();
    return m_mask.IsMatch(m_address, destIpAddress);
}

} // namespace ns3
