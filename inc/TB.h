#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

SC_MODULE(test_bench)
{
  /* Instancier les I/O */
  /*sc_out<sc_logic> A, B; 
  sc_in<sc_logic> result;*/
  int data;

  void Test();

  tlm_utils::simple_initiator_socket<test_bench> socket;

  /* Constructeur de la classe */
  SC_CTOR(test_bench) : socket("socket")
  {
    SC_THREAD(Test);
  }
};
