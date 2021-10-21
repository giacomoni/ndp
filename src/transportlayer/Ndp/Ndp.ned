package ndp.transportlayer.Ndp;

import ndp.transportlayer.contract.INdp;

simple Ndp like INdp
{
    parameters:
        int initialWindow = default(0);  // initialWindow size NDP-style (sender pushes IW pacakets)
        string ndpAlgorithmClass = default("NDPSimpleAlg");
        @display("i=block/wheelbarrow");

        @signal[packetReceivedFromUpper](type=cPacket);
        @signal[packetReceivedFromLower](type=cPacket);
    gates:
        input appIn @labels(NDPCommand/down) @messageKinds(inet::NdpCommandCode);
        input ipIn @labels(NdpHeader,Ipv4ControlInfo/up,Ipv6ControlInfo/up);
        output appOut @labels(NDPCommand/up) @messageKinds(inet::NdpStatusInd);
        output ipOut @labels(NdpHeader,Ipv4ControlInfo/down,Ipv6ControlInfo/down);
}

