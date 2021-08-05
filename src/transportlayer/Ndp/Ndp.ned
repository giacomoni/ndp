package ndp.transportlayer.Ndp;


import  ndp.transportlayer.contract.INdp;

simple Ndp like INdp
{
    parameters:
        bool delayedAcksEnabled = default(false); // delayed ACK algorithm (RFC 1122) enabled/disable
        bool timestampSupport = default(false); // Timestamps (RFC 1323) support (header option) (TS will be enabled for a connection if both endpoints support it)
        int mss = default(536); // Maximum Segment Size (RFC 793) (header option)
        int msl @unit(s) = default(120s);   // Maximum Segment Lifetime
         string ndpAlgorithmClass =default("NDPSimpleAlg");
        bool useDataNotification = default(false); // turn the notifications for arrived data on or off
        double stopOperationExtraTime @unit(s) = default(0s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation
        bool ecnWillingness = default(false);	// true if willing to use ECN
        @display("i=block/wheelbarrow");
		
		@signal[numRequestsRTOs](type=double);
        @statistic[numRequestsRTOs](title="numRequestsRTOs "; source=numRequestsRTOs; record=vector); 
        
        @signal[packetReceivedFromUpper](type=cPacket);
        @signal[packetReceivedFromLower](type=cPacket);
    gates:
        input appIn @labels(NDPCommand/down) @messageKinds(inet::NdpCommandCode);
        input ipIn @labels(NDPHeader,Ipv4ControlInfo/up,Ipv6ControlInfo/up);
        output appOut @labels(NDPCommand/up) @messageKinds(inet::NdpStatusInd);
        output ipOut @labels(NDPHeader,Ipv4ControlInfo/down,Ipv6ControlInfo/down);
}

