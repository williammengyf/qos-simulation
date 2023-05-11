#ifndef DESTINATION_PORT_NUMBER_H
#define DESTINATION_PORT_NUMBER_H

#include "filter-element.h"
#include "ns3/packet.h"

namespace ns3
{

class DestinationPortNumber : public FilterElement
{
public:
    DestinationPortNumber();
    DestinationPortNumber(uint16_t port);
    ~DestinationPortNumber() override;
    bool Match(Ptr<Packet> p) override;

private:
    uint32_t m_port;
};

}

#endif
