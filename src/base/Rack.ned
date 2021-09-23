
package ndp.base;
import inet.networklayer.configurator.ipv4.Ipv4FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import ndp.base.RouterNdp;
import inet.node.ethernet.EtherLink;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;
import inet.node.ethernet.Eth10M;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import ned.DatarateChannel;
import ned.IdealChannel;

import ndp.node.StandardHostNdp;
 
module Rack
{
    parameters:
        @Rack;
        // We get value from pod module.
        int k;
        int position;
        @display("bgb=600,250");

    gates:
        // As many ports as aggregation routers.
        inout rackg[int(k/2)];

    types:
        channel ethernetline extends DatarateChannel
        {
            delay = 1us;
//        datarate = 100Mbps;
           datarate = 1Gbps; 
        }

    submodules:
        // k/2 servers are connected with one edge router.
        servers[int(k/2)]: StandardHostNdp {
            // Reach value down.
  //           position = index;
            @display("p=80,160,r,80");
            @display("i=device/device");
        }
        // One edge or top of rack switch.
        edgeSwitch: RouterNdp { //no from type EdgeRouter.ned, because position is saved in Rack
            @display("p=300,80");
            @display("i=abstract/router");
          //  forwarding = default(true);
        }

//        ipconfig: EdgeIPConfig {
//            @display("p=560,31");
//        }
        
    //      configurator: IPv4NetworkConfigurator;

    connections:
        // Connect all servers with the one edge switch.
        for i=0..sizeof(servers)-1 {
            edgeSwitch.pppg++ <--> ethernetline <--> servers[i].pppg++;
        }
        // Connect the ports of the edge switch with the gates of the compound module.
        for i=0..int(k/2)-1 {
            edgeSwitch.pppg++ <--> IdealChannel <--> rackg++;
              
        }
}