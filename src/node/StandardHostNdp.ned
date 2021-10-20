

package ndp.node;

import inet.transportlayer.contract.ITcp;
import inet.applications.contract.IApp;
import inet.transportlayer.contract.ISctp;
import inet.transportlayer.contract.ITcp;
import inet.transportlayer.contract.IUdp;
import inet.applications.tunapp.TunnelApp;

import ndp.node.ApplicationLayerNodeBaseEcmp;
import ndp.networklayer.ipv4.Ipv4NetworkLayerEcmp;
import ndp.transportlayer.contract.INdp;
import ndp.application.contract.INdpApp;

module StandardHostNdp extends ApplicationLayerNodeBaseEcmp
{
    parameters:
        @display("i=device/pc2");
        @figure[submodules];

        *.routingTableModule = default("^.ipv4.routingTable");

}
