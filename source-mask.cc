#include "source-mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
SourceMask::SourceMask()
    : m_address(),
      m_mask()
{
}

/**
 * Constructor.
 * 
 * \param address Expected source IP address.
 * \param mask Expected source IP mask.
*/
SourceMask::SourceMask(const char* address, const char* mask)
    : m_address(address),
      m_mask(mask)
{
}

/**
 * Destructor.
*/
SourceMask::~SourceMask()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
bool
SourceMask::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    Ipv4Address srcIpAddress = ipv4Header.GetSource();
    return m_mask.IsMatch(m_address, srcIpAddress);
}

} // namespace ns3
