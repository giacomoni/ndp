

package ndp.transportlayer.contract;
 
moduleinterface INdp
{
    @display("i=block/wheelbarrow");
    gates:
        input appIn @labels(NDPCommand/down);
        input ipIn @labels(NdpHeader,IPv4ControlInfo/up,IPv6ControlInfo/up);
        output appOut @labels(NDPCommand/up);
        output ipOut @labels(NdpHeader,IPv4ControlInfo/down,IPv6ControlInfo/down);
}
