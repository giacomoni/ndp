package ndp.simulations.FatTreeNDP;
import inet.networklayer.configurator.ipv4.Ipv4FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import ndp.node.StandardHostNdp;
import ndp.common.scheduler.CentralSchedulerNdp;
import inet.node.inet.Router;
import ndp.base.RouterNdp;
import ndp.base.Pod;
import ndp.base.Rack;
import inet.node.ethernet.Eth100M;
import ndp.common.queue.NdpSwitchQueue;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import ecmp.networklayer.configurator.ipv4.Ipv4NetworkConfiguratorEcmp;
import inet.visualizer.contract.IIntegratedVisualizer;

import ned.DatarateChannel;
import ned.IdealChannel;


network FatTreeNdp
{
    parameters:
        // Only even values are allowed.
        int k = default(4);

        // Value for display string needed.
        int khalf = int(k/2);
        int kCore = int((k/2)^2);

        @display("bgb=1494.948,723.128,white");

    types:
        channel ethernetline extends DatarateChannel
        {
            delay =  1us;
            datarate = 1Gbps;
        }

    submodules:
        // A k-ary fattree consists of k pods.
        Pod[k]: Pod {
            // Reach values down.
            k = k;
            //@display("p=100,160,c,80");
            @display("p=347.06,324.268,r,120");
            @display("i=device/server");
            position = index;
        }

		// (k/2)^2 core routers.
        CoreRouter[kCore]: RouterNdp {
            //   k = k;
            //          position = index;
            @display("p=337.736,87.024,m,$kCore,120,150");
         //   @display("p=274.176,103.824005;is=vl");

        }

        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=305.665,67.625`");
        }
        configurator: Ipv4NetworkConfiguratorEcmp {
            @display("p=1314.495,672.2275");
        }
        centralScheduler: CentralSchedulerNdp {
            @display("p=704.06,601.0725;i=abstract/person,#17FF39;b=,,rect;is=vl;t=Central flow scheduler");
        }
//        multicastOrganiser: multicastOrganiser {
//            @display("p=385.735,601.0725");
//        }
    connections:


        for i=0..k-1, for j=0..sizeof(CoreRouter)-1 {
            Pod[i].podg++ <--> ethernetline <--> CoreRouter[j].pppg++;
        }

        // Core routers are connected with the Network Controller.
}


