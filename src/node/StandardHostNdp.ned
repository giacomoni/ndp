

package ndp.node;

import ndp.transportlayer.contract.INdp;
import ndp.application.contract.INdpApp;

import inet.transportlayer.contract.ITcp;

import inet.applications.contract.IApp;
//import inet.applications.contract.IPingApp;
//import inet.applications.contract.ISCTPApp;
//import inet.applications.contract.ITCPApp;
//import inet.applications.contract.IUDPApp;
import inet.transportlayer.contract.ISctp;
import inet.transportlayer.contract.ITcp;
import inet.transportlayer.contract.IUdp;
import inet.applications.tunapp.TunnelApp;
import ndp.node.ApplicationLayerNodeBaseNdp;
import ndp.networklayer.ipv4.Ipv4NetworkLayerNdp;

module StandardHostNdp extends ApplicationLayerNodeBaseNdp
{
    parameters:
        @display("i=device/pc2");
        @figure[submodules];
        ///////////// ndp  
        //int numNdpApps = default(0);
        //bool hasNdp = default(numNdpApps > 0);
        /////////////  
        *.routingTableModule = default("^.ipv4.routingTable");
 
    //submodules:

//
//        ndpApp[numApps]: <> like INdpApp {
//            @display("p=651,42,r,30");
//        }


}
