#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H

#include "ns3/packet.h"

namespace ns3
{

/**
 * Abstract class for filter elements.
*/
class FilterElement
{
public:
    virtual ~FilterElement() = default;
    virtual bool Match(Ptr<Packet> p) = 0;
};

} // namespace ns3

#endif
