#include "traffic-class.h"

namespace ns3
{

TrafficClass::TrafficClass()
    : m_bytes(0),
      m_packets(0),
      m_maxPackets(0),
      m_weight(0),
      m_priorityLevel(0),
      m_deficitCounter(0),
      m_isDefault(false),
      m_isActive(false)
{
}

TrafficClass::~TrafficClass()
{
    for (Filter* filter : m_filters)
    {
        delete filter;
    }
}

bool
TrafficClass::Enqueue(Ptr<Packet> p)
{
    if (m_maxPackets > 0 && m_packets >= m_maxPackets)
    {
        return false;
    }

    m_queue.push(p);
    m_packets++;
    m_bytes += p->GetSize();

    return true;
}

Ptr<Packet>
TrafficClass::Dequeue()
{
    if (m_queue.empty())
    {
        return nullptr;
    }

    Ptr<Packet> p = m_queue.front();
    m_queue.pop();
    m_packets--;
    m_bytes -= p->GetSize();

    return p;
}

Ptr<const Packet>
TrafficClass::Peek() const
{
    if (m_queue.empty())
    {
        return nullptr;
    }

    return m_queue.front();
}

bool
TrafficClass::Match(Ptr<Packet> p)
{
    for (Filter* filter : m_filters)
    {
        if (filter->Match(p))
        {
            return true;
        }
    }
    return false;
}

void
TrafficClass::SetMaxPackets(uint32_t maxPackets)
{
    m_maxPackets = maxPackets;
}

uint32_t
TrafficClass::GetMaxPackets()
{
    return m_maxPackets;
}

void
TrafficClass::SetWeight(uint32_t weight)
{
    m_weight = weight;
}

uint32_t
TrafficClass::GetWeight()
{
    return m_weight;
}

void
TrafficClass::SetPriorityLevel(uint32_t priorityLevel)
{
    m_priorityLevel = priorityLevel;
}

uint32_t
TrafficClass::GetPriorityLevel()
{
    return m_priorityLevel;
}

void
TrafficClass::IncreaseDeficit(uint32_t quantum)
{
    m_deficitCounter += quantum;
}

void
TrafficClass::DecreaseDeficit(uint32_t bytes)
{
    m_deficitCounter -= bytes;
}

uint32_t
TrafficClass::GetDeficitCounter()
{
    return m_deficitCounter;
}

void
TrafficClass::SetDefault(bool isDefault)
{
    m_isDefault = isDefault;
}

bool
TrafficClass::IsDefault()
{
    return m_isDefault;
}

void
TrafficClass::SetActive(bool isActive)
{
    m_isActive = isActive;
}

bool
TrafficClass::IsActive()
{
    return m_isActive;
}

} // namespace ns3
