#include "filter.h"

namespace ns3 {

/**
 * Constructor.
*/
Filter::Filter()
{
}

/**
 * Destructor.
*/
Filter::~Filter()
{
    for (FilterElement* element : m_elements)
    {
        delete element;
    }
}

/**
 * Adds a filter element to the filter.
 * 
 * \param element The filter element to add.
*/
void
Filter::AddElement(FilterElement* element)
{
    m_elements.push_back(element);
}

/**
 * Determines if a packet matches all filter element of the filter.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches all filter elements of the filter.
*/
bool
Filter::Match(Ptr<Packet> p)
{
    for (FilterElement* element : m_elements)
    {
        if (!element->Match(p))
        {
            return false;
        }
    }
    return true;
}

} // namespace ns3
