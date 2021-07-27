



package ndp.application.contract;


moduleinterface INdpApp
{
    parameters:
        @display("i=block/app");

    gates:
        input ndpIn @labels(NDPCommand/up);
        output ndpOut @labels(NDPCommand/down);
}

