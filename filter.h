#ifndef FILTER_H
#define FILTER_H

#include "filter-element.h"
#include "ns3/packet.h"

#include <vector>

namespace ns3
{

/**
 * Filter to classify packets.
*/
class Filter
{
public:
    std::vector<FilterElement*> m_elements;

    Filter();
    ~Filter();
    void AddElement(FilterElement* element);
    bool Match(Ptr<Packet> p);
};

} // namespace ns3

#endif
