

package ndp.simulations.SimpleSimulation;

@namespace(inet);
@namespace(ndp);


import ndp.node.StandardHostNdp;
import ndp.networklayer.configurator.ipv4.Ipv4NetworkConfiguratorEcmp;
import inet.node.inet.Router;
import ndp.base.RouterNdp;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;

network simplenetwork
{
    parameters:
    	@display("bgb=512,395");
    	int numberOfClients = default(1);
    	int numberOfNormalFlows = default(1);
    	int numberOfLongerFlows = default(2);
        int numberOfRouters = default(1);
    types:
        channel ethernetline extends DatarateChannel
        {
            delay =  1us;
            datarate = 1Gbps;
        }
    submodules:
        client[numberOfClients]: StandardHostNdp {
            @display("p=44,50,m,n,$numberOfClients,150");
        }
        configurator: Ipv4NetworkConfiguratorEcmp {
            @display("p=450,350");
        }
        server: StandardHostNdp {
            @display("p=431,50");
        }
        router[numberOfRouters]: RouterNdp {
            @display("p=252,50,m,n,$numberOfRouters,150");
        }
    connections:
        for i=0..sizeof(client)-1, for j=0..sizeof(router)-1 {
            client[i].pppg++ <--> ethernetline <--> router[j].pppg++;
        }
        for i=0..sizeof(router)-1{
            router[i].pppg++ <--> ethernetline <--> server.pppg++;
        }
} 
