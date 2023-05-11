#ifndef SOURCE_PORT_NUMBER_H
#define SOURCE_PORT_NUMBER_H

#include "filter-element.h"
#include "ns3/packet.h"

namespace ns3
{

class SourcePortNumber : public FilterElement
{
public:
    SourcePortNumber();
    SourcePortNumber(uint16_t port);
    ~SourcePortNumber() override;
    bool Match(Ptr<Packet> p) override;

private:
    uint32_t m_port;
};

}

#endif
