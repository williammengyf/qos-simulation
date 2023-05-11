#include "source-port-number.h"
#include "ns3/ipv4-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"

namespace ns3 {

SourcePortNumber::SourcePortNumber()
    : m_port(0)
{
}

SourcePortNumber::SourcePortNumber(uint16_t port)
    : m_port(port)
{
}

SourcePortNumber::~SourcePortNumber()
{
}

bool
SourcePortNumber::Match(Ptr<Packet> p)
{
    Ptr<Packet> copy = p->Copy();

    PppHeader pppHeader;
    copy->RemoveHeader(pppHeader);

    Ipv4Header ipv4Header;
    copy->RemoveHeader(ipv4Header);

    uint16_t srcPort = 0;
    uint8_t protocol = ipv4Header.GetProtocol();

    const uint8_t PROT_NUM_TCP = 6;
    const uint8_t PROT_NUM_UDP = 17;

    if (protocol == PROT_NUM_TCP)
    {
        TcpHeader tcpHeader;
        copy->RemoveHeader(tcpHeader);
        srcPort = tcpHeader.GetSourcePort();
    }
    else if (protocol == PROT_NUM_UDP)
    {
        UdpHeader udpHeader;
        copy->RemoveHeader(udpHeader);
        srcPort = udpHeader.GetSourcePort();
    }

    return srcPort == static_cast<uint16_t>(m_port);
}

}
