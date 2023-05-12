#include "protocol-number.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
ProtocolNumber::ProtocolNumber()
    : m_protocol(0)
{
}

/**
 * Constructor.
 * 
 * \param protocol Expected protocol number.
*/
ProtocolNumber::ProtocolNumber(uint8_t protocol)
    : m_protocol(protocol)
{
}

/**
 * Destructor.
*/
ProtocolNumber::~ProtocolNumber()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
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

} // namespace ns3
