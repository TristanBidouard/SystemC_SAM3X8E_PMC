#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

#define SIZE 256
#define REGISTERBEGIN 0x400E0600

using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

class memory{
    public:
        int data;
        int adr;
        char* type; // 'R', 'W', 'A', 'X'
    
        int read();
        int write(int data_in);
};

class socket_PMC {
    private:
        bool ce_UART;
        string name;

    public:
        void enable();
        void disable();
        socket_PMC(string nom);
        tlm_utils::simple_initiator_socket<socket_PMC> socket;
};

SC_MODULE(IP_PMC)
{
    void pmc_constructor();
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
    memory mem[68];

    tlm_utils::simple_target_socket<IP_PMC> socket;
    tlm_utils::simple_initiator_socket<IP_PMC> socket_timer;

    socket_PMC* socket_UART_o[4];

    socket_PMC* socket_GPIO_o[4];

    void memory_init();

    void enable_timer();
    void disable_timer();

    unsigned char ce_timer;

    SC_CTOR(IP_PMC) : socket("socket"), socket_timer("socket_timer")
    {
        socket.register_b_transport(this, &IP_PMC::b_transport);

        for (int i = 0 ; i < 4 ; i++) {
            socket_UART_o[i] = new socket_PMC("UART");
            socket_GPIO_o[i] = new socket_PMC("GPIO");
        } 

        memory_init();   

        SC_THREAD(pmc_constructor);
    }
}; 

