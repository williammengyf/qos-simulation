#include "destination-mask.h"

#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

DestinationMask::DestinationMask()
    : m_address(),
      m_mask()
{
}

DestinationMask::DestinationMask(const char* address, const char* mask)
    : m_address(address),
      m_mask(mask)
{
}

DestinationMask::~DestinationMask()
{
}

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

}
