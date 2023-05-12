#include "drr.h"
#include "filter.h"
#include "spq.h"
#include "traffic-class.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
 
using namespace ns3;

int
main(int argc, char *argv[])
{
    std::string config = "./scratch/qos-simulation/spq-config.xml";
    std::string mode = "SPQ";

    CommandLine cmd(__FILE__);
    cmd.AddValue("config", "Path of the config file", config);
    cmd.AddValue("mode", "QoS mechanism to simulate", mode);
    cmd.Parse(argc, argv);

    std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c){ return std::tolower(c); });

    Ptr<DiffServ> queue;
    if (mode == "spq")
    {
        queue = Create<Spq>();
    }
    else if (mode == "drr")
    {
        queue = Create<Drr>();
    }
    else
    {
        return 1;
    }

    if (!queue->LoadConfig(config.c_str()))
    {
        std::cout << "Error loading file " << config << std::endl;
        return 1;
    }
    
    Time::SetResolution(Time::NS);

    NodeContainer nodes;
    nodes.Create(3);

    PointToPointHelper pointToPointCR, pointToPointRS;
    pointToPointCR.SetDeviceAttribute("DataRate", StringValue("4Mbps"));
    pointToPointCR.SetChannelAttribute("Delay", StringValue("2ms"));
    pointToPointRS.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    pointToPointRS.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer devicesCR, devicesRS;
    devicesCR = pointToPointCR.Install(nodes.Get(0), nodes.Get(1));
    devicesRS = pointToPointRS.Install(nodes.Get(1), nodes.Get(2));

    pointToPointCR.EnablePcapAll(mode + "-simulation");

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesCR = address.Assign(devicesCR);
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesRS = address.Assign(devicesRS);

    Ptr<ns3::PointToPointNetDevice> p2pDeviceCR = DynamicCast<ns3::PointToPointNetDevice>(nodes.Get(1)->GetDevice(0));
    p2pDeviceCR->SetQueue(queue);
    Ptr<ns3::PointToPointNetDevice> p2pDeviceRS = DynamicCast<ns3::PointToPointNetDevice>(nodes.Get(1)->GetDevice(1));
    p2pDeviceRS->SetQueue(queue);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    PacketSinkHelper sink1("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), 10000));
    ApplicationContainer serverApps1 = sink1.Install(nodes.Get(2));
    serverApps1.Start(Seconds(0.0));
    serverApps1.Stop(Seconds(50.0));

    PacketSinkHelper sink2("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), 20000));
    ApplicationContainer serverApps2 = sink2.Install(nodes.Get(2));
    serverApps2.Start(Seconds(0.0));
    serverApps2.Stop(Seconds(50.0));

    PacketSinkHelper sink3("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), 30000));
    ApplicationContainer serverApps3 = sink3.Install(nodes.Get(2));
    serverApps3.Start(Seconds(0.0));
    serverApps3.Stop(Seconds(50.0));

    if (mode == "spq")
    {
        UdpClientHelper client1(interfacesRS.GetAddress(1), 10000);
        client1.SetAttribute("MaxPackets", UintegerValue(10000));
        client1.SetAttribute("Interval", TimeValue(MilliSeconds(1.0)));
        client1.SetAttribute("PacketSize", UintegerValue(1024));

        UdpClientHelper client2(interfacesRS.GetAddress(1), 20000);
        client2.SetAttribute("MaxPackets", UintegerValue(10000));
        client2.SetAttribute("Interval", TimeValue(MilliSeconds(1.0)));
        client2.SetAttribute("PacketSize", UintegerValue(1024));

        ApplicationContainer clientApps1 = client1.Install(nodes.Get(0));
        clientApps1.Start(Seconds(4.0));
        clientApps1.Stop(Seconds(5.0));

        ApplicationContainer clientApps2 = client2.Install(nodes.Get(0));
        clientApps2.Start(Seconds(1.0));
        clientApps2.Stop(Seconds(5.0));
    }
    else
    {
        UdpClientHelper client1(interfacesRS.GetAddress(1), 10000);
        client1.SetAttribute("MaxPackets", UintegerValue(10000));
        client1.SetAttribute("Interval", TimeValue(MilliSeconds(1.0)));
        client1.SetAttribute("PacketSize", UintegerValue(1024));

        UdpClientHelper client2(interfacesRS.GetAddress(1), 20000);
        client2.SetAttribute("MaxPackets", UintegerValue(10000));
        client2.SetAttribute("Interval", TimeValue(MilliSeconds(1.0)));
        client2.SetAttribute("PacketSize", UintegerValue(1024));

        UdpClientHelper client3(interfacesRS.GetAddress(1), 30000);
        client3.SetAttribute("MaxPackets", UintegerValue(10000));
        client3.SetAttribute("Interval", TimeValue(MilliSeconds(1.0)));
        client3.SetAttribute("PacketSize", UintegerValue(1024));

        ApplicationContainer clientApps1 = client1.Install(nodes.Get(0));
        clientApps1.Start(Seconds(3.0));
        clientApps1.Stop(Seconds(5.0));

        ApplicationContainer clientApps2 = client2.Install(nodes.Get(0));
        clientApps2.Start(Seconds(3.0));
        clientApps2.Stop(Seconds(5.0));

        ApplicationContainer clientApps3 = client3.Install(nodes.Get(0));
        clientApps3.Start(Seconds(3.0));
        clientApps3.Stop(Seconds(5.0));
    }

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
