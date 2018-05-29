#include "IP_PMC.h"

void IP_PMC::test()                  // a C++ function
{
    /*SUM.write(A.read() + B.read());*/

    cout << "Coucou je suis l'IP PMC " << endl;

    socket.register_b_transport(this, &IP_PMC::b_transport);
}

void IP_PMC::b_transport( tlm::tlm_generic_payload& trans, sc_time& delay)
{
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}
