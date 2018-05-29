#include <iostream>
#include "systemc.h"

#include "TB.h"
#include "IP_PMC.h"

using namespace std;

int sc_main(int argc, char* argv[])
{

    /*sc_signal<sc_logic> ASig, BSig, SumSig;*/

    /* Creer un module PMC */
    IP_PMC pmc("NotrePmc");

    /* Creer le module test bench */
    test_bench test_bench("NotreTb");

    test_bench.socket.bind(pmc.socket);

    /*Stim1.A(ASig);
    Stim1.B(BSig);
    Stim1.result(SumSig);

    add DUT("add");
    DUT.A(ASig);
    DUT.B(BSig);
    DUT.SUM(SumSig);*/

    sc_start();
    return 0;
}

