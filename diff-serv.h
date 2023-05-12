#ifndef DIFF_SERV_H
#define DIFF_SERV_H

#include "traffic-class.h"
#include "ns3/packet.h"
#include "ns3/queue.h"

#include <vector>

namespace ns3
{

/**
 * Queue for differentiated services.
*/
class DiffServ : public Queue<Packet>
{
public:
    DiffServ();
    ~DiffServ() override;
    bool LoadConfig(const char* filename);
    bool Enqueue(Ptr<Packet> p) override;
    Ptr<Packet> Dequeue() override;
    Ptr<Packet> Remove() override;
    Ptr<const Packet> Peek() const override;
    void AddClass(TrafficClass* trafficClass);
    virtual Ptr<Packet> Schedule() = 0;
    uint32_t Classify(Ptr<Packet> p);

protected:
    std::vector<TrafficClass*> q_class;

    virtual uint32_t NextClass() const = 0;

private:
    bool DoEnqueue(Ptr<Packet> p);
    Ptr<Packet> DoDequeue();
    Ptr<Packet> DoRemove();
    Ptr<const Packet> DoPeek() const;
    using Queue<Packet>::DropBeforeEnqueue;
    using Queue<Packet>::DropAfterDequeue;
};

} // namespace ns3

#endif
