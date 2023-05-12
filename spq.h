#ifndef SPQ_H
#define SPQ_H

#include "diff-serv.h"

namespace ns3
{

/**
 * Queue with SPQ mechanism.
*/
class Spq : public DiffServ
{
public:
    Spq();
    ~Spq();
    Ptr<Packet> Schedule() override;

protected:
    uint32_t NextClass() const override;
};

} // namespace ns3

#endif
