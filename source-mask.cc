#include "source-mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

SourceMask::SourceMask()
    : m_address(),
      m_mask()
{
}

SourceMask::SourceMask(const char* address, const char* mask)
    : m_address(address),
      m_mask(mask)
{
}

SourceMask::~SourceMask()
{
}

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

}
