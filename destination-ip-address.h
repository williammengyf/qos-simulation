#ifndef DESTINATION_IP_ADDRESS_H
#define DESTINATION_IP_ADDRESS_H

#include "filter-element.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * Filter element for destination IP address.
*/
class DestinationIpAddress : public FilterElement
{
public:
    DestinationIpAddress();
    DestinationIpAddress(const char* address);
    ~DestinationIpAddress() override;
    bool Match(Ptr<Packet> p) override;

private:
    Ipv4Address m_address;
};

} // namespace ns3

#endif
