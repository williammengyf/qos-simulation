#include "filter.h"

namespace ns3 {

Filter::Filter()
{
}

Filter::~Filter()
{
    for (FilterElement* element : m_elements)
    {
        delete element;
    }
}

void
Filter::AddElement(FilterElement* element)
{
    m_elements.push_back(element);
}

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

}
