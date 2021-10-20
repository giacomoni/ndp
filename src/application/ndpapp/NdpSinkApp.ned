
package ndp.application.ndpapp;
import ndp.application.contract.INdpApp;
import inet.applications.contract.IApp;
simple NdpSinkApp like IApp
{
    parameters:
        volatile string localAddress = default(""); // may be left empty ("")
        volatile int localPort; // port number to listen on
        @class("inet::NdpSinkApp");
        @display("i=block/sink");
        double multiCastGroupId = default(-1);
        double multiSrcGroupId = default(-1);
        // moh
        bool isBackroundFlow = default(false);

        @signal[numRcvTrimmedHeaderSigNdp](type=double);
        @statistic[numRcvTrimmedHeaderSigNdp](title="numRcvTrimmedHeaderNdp"; source=numRcvTrimmedHeaderSigNdp; unit=s; record=last);

        @signal[multicastGroupIdSignal](type=double);
        @statistic[multicastGroupIdSignal](title="multicastGroupIdSignal "; source=multicastGroupIdSignal; unit=s; record=last);

        @signal[multisourceGroupIdSignal](type=double);
        @statistic[multisourceGroupIdSignal](title="multisourceGroupIdSignal "; source=multisourceGroupIdSignal; unit=s; record=last);


        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="NDP Session's flow completion time"; source=fctRecordv3; unit=s; record=last);

        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets (symbols) received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

         // MOH: FCT using ResultFilter.cc (messageAge)
//       @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);

        //@statistic[mohThroughputNDP](title="mohThroughputNDP"; source="throughput(packetReceived)"; unit=bps; record=mean); //ResultsFilter.cc
        @statistic[instThroughputNDP](title="instThroughputNDP"; source="throughputA(packetReceived)"; unit=bps; record=mean,vector); //ResultsFilter.cc
        @signal[goodputSigNdp](type=double);
        @statistic[mohThroughputNDP](title="mohThroughputNDP"; source=goodputSigNdp; unit=bps; record=last); //ResultsFilter.cc
        //TODO
    gates:
        input socketIn @labels(NDPCommand/up);
        output socketOut @labels(NDPCommand/down);
}

