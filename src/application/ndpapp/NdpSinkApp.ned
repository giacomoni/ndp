
package ndp.application.ndpapp;

import inet.applications.contract.IApp;

simple NdpSinkApp like IApp
{
    parameters:
        volatile string localAddress = default(""); // may be left empty ("")
        volatile int localPort; // port number to listen on
        
        bool recordStatistics = default(true);
        
        @class("inet::NdpSinkApp");
        @display("i=block/sink");

        @signal[numRcvTrimmedHeaderSigNdp](type=double);
        @statistic[numRcvTrimmedHeaderSigNdp](title="numRcvTrimmedHeaderNdp"; source=numRcvTrimmedHeaderSigNdp; unit=s; record=last);

        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="NDP Session's flow completion time"; source=fctRecordv3; unit=s; record=last);

        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets (symbols) received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

        @statistic[instThroughputNDP](title="instThroughputNDP"; source="throughputA(packetReceived)"; unit=bps; record=mean,vector); //ResultsFilter.cc
        @signal[goodputSigNdp](type=double);
        @statistic[mohThroughputNDP](title="mohThroughputNDP"; source=goodputSigNdp; unit=bps; record=last); //ResultsFilter.cc
    gates:
        input socketIn @labels(NDPCommand/up);
        output socketOut @labels(NDPCommand/down);
}

