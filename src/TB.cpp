#include "TB.h"

void test_bench::Test()
{
    /* Ecrire des valeurs sur les I/O */
    /*A.write(A_in);
    B.write(B_in);*/

    /*wait(10,SC_NS);*/

    /* Afficher les resultats */
    /*cout << "A = " << A << endl;

    cout << "B = " << B << endl;*/

    cout << "Coucou je suis le test bench " << endl;

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    sc_time delay = sc_time(10, SC_NS);

    for (int i = 32; i < 96; i += 4)
    {
        tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
        if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

        trans->set_command( cmd );
        trans->set_address( i );
        trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
        trans->set_data_length( 4 );
        trans->set_byte_enable_ptr( 0 );
        trans->set_dmi_allowed( false );
        trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );
        socket->b_transport(*trans, delay);
        wait(delay);
    }
}
