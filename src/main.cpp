#include <iostream>
#include "systemc.h"

#include "TB.h"
#include "IP_PMC.h"

using namespace std;

int sc_main(int argc, char* argv[])
{
    int i;

    /* Creer un module PMC */
    IP_PMC pmc_o("module_Pmc");

    /* Creer le module cortex */
    cortex cortex_o("module_Processeur");

    /* Creer le module timer */
    timer timer_o("module_Timer");

    /* Creer le module UART */
    UART UART_o("module_UART");

    /* Creer le module GPIO */
    GPIO GPIO_o("module_GPIO");

    /* Linker les sockets */
    cortex_o.socket.bind(pmc_o.socket);
    pmc_o.socket_timer.bind(timer_o.socket_timer);
    for (i = 0 ; i < 4 ; i++) {
        pmc_o.socket_UART_o[i]->socket.bind(UART_o.socket_UART[i]->socket);
        pmc_o.socket_GPIO_o[i]->socket.bind(GPIO_o.socket_GPIO[i]->socket);
    }

    sc_start();

    return 0;
}

