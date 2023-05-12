#ifndef DRR_H
#define DRR_H

#include "diff-serv.h"

namespace ns3
{

/**
 * Queue with DRR mechanism.
*/
class Drr : public DiffServ
{
public:
    Drr();
    ~Drr();
    Ptr<Packet> Schedule() override;

protected:    
    uint32_t NextClass() const override;
};
    
} // namespace ns3

#endif
