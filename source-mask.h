#ifndef SOURCE_MASK_H
#define SOURCE_MASK_H

#include "filter-element.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * Filter element for source mask.
*/
class SourceMask : public FilterElement
{
public:
    SourceMask();
    SourceMask(const char* address, const char* mask);
    ~SourceMask() override;
    bool Match(Ptr<Packet> p) override;

private:
    Ipv4Address m_address;
    Ipv4Mask m_mask;
};

} // namespace ns3

#endif
