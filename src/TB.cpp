#include "TB.h"

void cortex::cortex_constructor()
{
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    sc_time delay = sc_time(10, SC_NS);

    for (int i = 32; i < 96; i += 4)
    {
        tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
        if (cmd == tlm::TLM_WRITE_COMMAND) data = 0x00000002;

        trans->set_command( cmd );
        trans->set_address( ADR );
        trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
        trans->set_data_length( 4 );
        trans->set_byte_enable_ptr( 0 );
        trans->set_dmi_allowed( false );
        trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

        cout << "--------------------- EMISSION --------------------" << endl;
        cout << "envoi commande : "  << cmd <<endl;
        cout << "envoi address : " << hex << ADR << endl;
        cout << "envoi data : " << data << endl;
        cout << "---------------------------------------------------" << endl;

        socket->b_transport(*trans, delay);

         if ( trans->is_response_error() )

        wait(delay);
    }
}

// Handler reception socket timer
void timer::b_transport (tlm::tlm_generic_payload& trans, sc_time& delay)
{
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  cout << "Timer: Message arrivé"  << endl;

  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

void timer::timer_constructor () {
    cout << "Je suis le timer" <<endl;
}

// Handler reception socket UART
void socket_tb::b_transport (tlm::tlm_generic_payload& trans, sc_time& delay)
{
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  cout << name << (*ptr ? " : ENABLE" : " : DISABLE") << endl;

  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

socket_tb::socket_tb(string nom) : socket("socket_UART_tb") {
    name = nom;
    socket.register_b_transport(this, &socket_tb::b_transport);
}

