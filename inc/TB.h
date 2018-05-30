#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

#define ADR 0x400E0704

using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class socket_tb {
    private:
        string name;

    public:
        void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
        tlm_utils::simple_target_socket<socket_tb> socket;
        socket_tb(string name);
};

SC_MODULE(cortex)
{
    int data;

    void cortex_constructor();

    tlm_utils::simple_initiator_socket<cortex> socket;

    /* Constructeur de la classe */
    SC_CTOR(cortex) : socket("socket"){
        SC_THREAD(cortex_constructor);
    }
};

SC_MODULE(GPIO)
{
    socket_tb* socket_GPIO[4];

    SC_CTOR(GPIO){
    for (int i = 0 ; i < 4 ; i++)
        socket_GPIO[i] = new socket_tb("GPIO");
    }
};

SC_MODULE(UART)
{
    socket_tb* socket_UART[4];

    /* Constructeur de la classe UART */
    SC_CTOR(UART){
    for (int i = 0 ; i < 4 ; i++)
        socket_UART[i] = new socket_tb("UART");
    }
};


SC_MODULE(timer)
{
    int data;

    void timer_constructor();

    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);

    tlm_utils::simple_target_socket<timer> socket_timer;

    /* Constructeur de la classe timer */
    SC_CTOR(timer) : socket_timer("socket_timer"){
        socket_timer.register_b_transport(this, &timer::b_transport);
        SC_THREAD(timer_constructor);
    }
};
