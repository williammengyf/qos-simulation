#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H

#include "ns3/packet.h"

namespace ns3
{

class FilterElement
{
public:
    virtual ~FilterElement() = default;
    virtual bool Match(Ptr<Packet> p) = 0;
};

}

#endif
