

package ndp.application.ndpapp;

import ndp.application.contract.INdpApp;

simple NdpEchoApp extends NdpServerHostApp
{
    parameters:
        @class(NdpEchoApp);
        double echoFactor = default(1);
        double echoDelay @unit(s) = default(0s);
        serverThreadModuleType = default("inet.applications.ndpapp.NdpEchoAppThread"); // module type of "thread" module to launch on incoming connections
        @display("i=block/app");
        @signal[packetSent](type=inet::Packet);
        @signal[packetReceived](type=cPacket);
		@statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[packetSent](title="packets sent"; source=packetSent; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,weightedHistogram,vector; interpolationmode=none);
}

// Thread for ~NdpEchoApp
simple NdpEchoAppThread
{
}