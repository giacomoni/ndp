

package ndp.simulations;

@namespace(inet);
@namespace(ndp);


import ndp.node.StandardHostNdp;
import inet.networklayer.configurator.ipv4.Ipv4FlatNetworkConfigurator;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import ndp.networklayer.configurator.ipv4.Ipv4NetworkConfiguratorEcmp;
import inet.node.inet.Router;
import ndp.base.RouterNdp;
//import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;


//
// TODO auto-generated type
//
network simplenetwork
{
    @display("bgb=512,395");
    submodules:
        client: StandardHostNdp {
            @display("p=44,213");
        }

        client2: StandardHostNdp {
            @display("p=50,312");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=295,91");
        }
        server: StandardHostNdp {
            @display("p=431,190");
        }
        router: RouterNdp {
            @display("p=252,256");
        }
    connections:
        router.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> server.pppg++;
        client.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> router.pppg++;


        router.pppg++   <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> client2.pppg++;
}
