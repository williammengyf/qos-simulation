#include "traffic-class.h"

namespace ns3
{

/**
 * Constructor.
*/
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

/**
 * Destructor.
*/
TrafficClass::~TrafficClass()
{
    for (Filter* filter : m_filters)
    {
        delete filter;
    }
}

/**
 * Places a packet to the back of the queue.
 * 
 * \param p Pointer to the packet.
 * \returns True if succeeded.
*/
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

/**
 * Removes a packet from the front of the queue.
 * 
 * \returns Pointer to the packet.
*/
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

/**
 * Retrieves, but does not remove a packet from the front of the queue.
 * 
 * \returns Pointer to the packet.
*/
Ptr<const Packet>
TrafficClass::Peek() const
{
    if (m_queue.empty())
    {
        return nullptr;
    }

    return m_queue.front();
}

/**
 * Determines if a packet matches any filter of the traffic class.
 * 
 * \param p Pointer to the packet.
 * \returns True if the packet matches any filter of the traffic class.
*/
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

/**
 * Sets max packets of the traffic class.
 * 
 * \param maxPackets Max packets.
*/
void
TrafficClass::SetMaxPackets(uint32_t maxPackets)
{
    m_maxPackets = maxPackets;
}

/**
 * Gets max packets of the traffic class.
 * 
 * \returns Max packets.
*/
uint32_t
TrafficClass::GetMaxPackets()
{
    return m_maxPackets;
}

/**
 * Sets weight of the traffic class.
 * 
 * \param weight Weight.
*/
void
TrafficClass::SetWeight(uint32_t weight)
{
    m_weight = weight;
}

/**
 * Gets weight of the traffic class.
 * 
 * \returns Weight of the traffic class.
*/
uint32_t
TrafficClass::GetWeight()
{
    return m_weight;
}

/**
 * Sets priority level of the traffic class.
 * 
 * \param priorityLevel Priority level.
*/
void
TrafficClass::SetPriorityLevel(uint32_t priorityLevel)
{
    m_priorityLevel = priorityLevel;
}

/**
 * Gets priority level of the traffic class.
 * 
 * \returns Priority level.
*/
uint32_t
TrafficClass::GetPriorityLevel()
{
    return m_priorityLevel;
}

/**
 * Increases deficit counter of the traffic class.
 * 
 * \param quantum Quantum to add to the deficit counter.
*/
void
TrafficClass::IncreaseDeficit(uint32_t quantum)
{
    m_deficitCounter += quantum;
}

/**
 * Decreases deficit counter of the traffic class.
 * 
 * \param bytes Bytes to subtract from the deficit counter.
*/
void
TrafficClass::DecreaseDeficit(uint32_t bytes)
{
    m_deficitCounter -= bytes;
}

/**
 * Gets the dificit counter of the traffic class.
 * 
 * \returns Deficit Counter
*/
uint32_t
TrafficClass::GetDeficitCounter()
{
    return m_deficitCounter;
}

/**
 * Sets if the traffic class is default.
 * 
 * \param isDefault If the traffic class is default.
*/
void
TrafficClass::SetDefault(bool isDefault)
{
    m_isDefault = isDefault;
}

/**
 * Gets if the traffic class is default.
 * 
 * \returns True if the traffic class is default.
*/
bool
TrafficClass::IsDefault()
{
    return m_isDefault;
}

/**
 * Sets if the traffic class is active.
 * 
 * \param isActive If the traffic class is active.
*/
void
TrafficClass::SetActive(bool isActive)
{
    m_isActive = isActive;
}

/**
 * Gets if the traffic class is active.
 * 
 * \returns True if the traffic class is active.
*/
bool
TrafficClass::IsActive()
{
    return m_isActive;
}

} // namespace ns3
