#ifndef TRAFFIC_CLASS_H
#define TRAFFIC_CLASS_H

#include "filter.h"
#include "ns3/packet.h"

#include <queue>
#include <vector>

namespace ns3
{

/**
 * Queue of packets with characteristics.
*/
class TrafficClass
{
public:
    std::vector<Filter*> m_filters;

    TrafficClass();
    ~TrafficClass();
    bool Enqueue(Ptr<Packet> p);
    Ptr<Packet> Dequeue();
    Ptr<const Packet> Peek() const;
    bool Match(Ptr<Packet> p);
    void SetMaxPackets(uint32_t maxPackets);
    uint32_t GetMaxPackets();
    void SetWeight(uint32_t weight);
    uint32_t GetWeight();
    void SetPriorityLevel(uint32_t priorityLevel);
    uint32_t GetPriorityLevel();
    void IncreaseDeficit(uint32_t quantum);
    void DecreaseDeficit(uint32_t bytes);
    uint32_t GetDeficitCounter();
    void SetDefault(bool isDefault);
    bool IsDefault();
    void SetActive(bool isActive);
    bool IsActive();

private:
    std::queue<Ptr<Packet>> m_queue;

    uint32_t m_bytes;
    uint32_t m_packets;
    uint32_t m_maxPackets;
    uint32_t m_weight;
    uint32_t m_priorityLevel;
    uint32_t m_deficitCounter;
    bool m_isDefault;
    bool m_isActive;
};

} // namespace ns3

#endif
