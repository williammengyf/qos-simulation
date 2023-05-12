#include "destination-port-number.h"

#include "ns3/ipv4-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"

namespace ns3 {

/**
 * Constructor.
*/
DestinationPortNumber::DestinationPortNumber()
    : m_port(0)
{
}

/**
 * Constructor.
 * 
 * \param port Expected destination port number.
*/
DestinationPortNumber::DestinationPortNumber(uint16_t port)
    : m_port(port)
{
}

/**
 * Destructor.
*/
DestinationPortNumber::~DestinationPortNumber()
{
}

/**
 * Determines if a packet matches the filter element.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches the filter element.
*/
bool
DestinationPortNumber::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    uint16_t destPort = 0;
    uint8_t protocol = ipv4Header.GetProtocol();

    const uint8_t PROT_NUM_TCP = 6;
    const uint8_t PROT_NUM_UDP = 17;

    if (protocol == PROT_NUM_TCP)
    {
        TcpHeader tcpHeader;
        copy->RemoveHeader(tcpHeader);
        destPort = tcpHeader.GetDestinationPort();
    }
    else if (protocol == PROT_NUM_UDP)
    {
        UdpHeader udpHeader;
        copy->RemoveHeader(udpHeader);
        destPort = udpHeader.GetDestinationPort();
    }

    return destPort == static_cast<uint16_t>(m_port);
}

} // namespace ns3
