#ifndef SOURCE_IP_ADDRESS_H
#define SOURCE_IP_ADDRESS_H

#include "filter-element.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

namespace ns3
{

class SourceIpAddress : public FilterElement
{
public:
    SourceIpAddress();
    SourceIpAddress(const char* address);
    ~SourceIpAddress() override;
    bool Match(Ptr<Packet> p) override;

private:
    Ipv4Address m_address;
};

}

#endif
