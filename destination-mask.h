#ifndef DESTINATION_MASK_H
#define DESTINATION_MASK_H

#include "filter-element.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

namespace ns3
{

class DestinationMask : public FilterElement
{
public:
    DestinationMask();
    DestinationMask(const char* address, const char* mask);
    ~DestinationMask() override;
    bool Match(Ptr<Packet> p) override;

private:
    Ipv4Address m_address;
    Ipv4Mask m_mask;
};

}

#endif
