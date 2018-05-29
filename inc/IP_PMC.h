#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

SC_MODULE(IP_PMC)
{
  /*sc_in<sc_logic> > A, B; */         // input signal ports
  /*sc_out<sc_logic> > SUM;    */      // output signal ports

  void test();
  void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);

  tlm_utils::simple_target_socket<IP_PMC> socket;

  SC_CTOR(IP_PMC) : socket("socket")
  {
    SC_THREAD(test);           // register do_add with kernel
  }
}; 
