#include "drr.h"
#include "traffic-class.h"

namespace ns3
{

Drr::Drr()
    : DiffServ()
{
}

Drr::~Drr()
{
}

Ptr<Packet>
Drr::Schedule()
{
    uint32_t index = 0;
    uint32_t activeClass = q_class.size();
    bool isEmpty = true;

    for (TrafficClass* trafficClass : q_class)
    {
        if (trafficClass->IsActive())
        {
            activeClass = index;
        }

        if (trafficClass->Peek())
        {
            isEmpty = false;
        }

        index++;
    }

    if (isEmpty)
    {
        return nullptr;
    }

    if (activeClass == q_class.size())
    {
        index = 0;
        uint32_t quantum = q_class[index]->GetWeight();
        q_class[index]->IncreaseDeficit(quantum);
    }
    else
    {
        index = activeClass;
        q_class[index]->SetActive(false);
    }

    while (!q_class[index]->Peek() || q_class[index]->Peek()->GetSize() > q_class[index]->GetDeficitCounter())
    {
        index = (index + 1) % q_class.size();
        uint32_t quantum = q_class[index]->GetWeight();
        q_class[index]->IncreaseDeficit(quantum);
    }

    Ptr<Packet> p = q_class[index]->Dequeue();
    if (p)
    {
        q_class[index]->DecreaseDeficit(p->GetSize());
        q_class[index]->SetActive(true);
    }

    return p;
}

uint32_t
Drr::NextClass() const
{
    uint32_t index = 0;
    uint32_t activeClass = q_class.size();
    bool isEmpty = true;
    std::vector<uint32_t> deficitCounter;

    for (TrafficClass* trafficClass : q_class)
    {
        if (trafficClass->IsActive())
        {
            activeClass = index;
        }

        if (trafficClass->Peek())
        {
            isEmpty = false;
        }

        deficitCounter.push_back(trafficClass->GetDeficitCounter());
        index++;
    }

    if (isEmpty)
    {
        return q_class.size();
    }

    if (activeClass == q_class.size())
    {
        index = 0;
        uint32_t quantum = q_class[index]->GetWeight();
        deficitCounter[index] += quantum;
    }
    else
    {
        index = activeClass;
    }

    while (!q_class[index]->Peek() || q_class[index]->Peek()->GetSize() > deficitCounter[index])
    {
        index = (index + 1) % q_class.size();
        uint32_t quantum = q_class[index]->GetWeight();
        deficitCounter[index] += quantum;
    }

    return index;
}

} // namespace ns3
