#ifndef PROTOCOL_NUMBER_H
#define PROTOCOL_NUMBER_H

#include "filter-element.h"
#include "ns3/packet.h"

namespace ns3
{

class ProtocolNumber : public FilterElement
{
public:
    ProtocolNumber();
    ProtocolNumber(uint8_t protocol);
    ~ProtocolNumber() override;
    bool Match(Ptr<Packet> p) override;

private:
    uint32_t m_protocol;
};

}

#endif
