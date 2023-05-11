#include "protocol-number.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

ProtocolNumber::ProtocolNumber()
    : m_protocol(0)
{
}

ProtocolNumber::ProtocolNumber(uint8_t protocol)
    : m_protocol(protocol)
{
}

ProtocolNumber::~ProtocolNumber()
{
}

bool
ProtocolNumber::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    uint8_t protocol = ipv4Header.GetProtocol();
    return protocol == static_cast<uint8_t>(m_protocol);
}

}
