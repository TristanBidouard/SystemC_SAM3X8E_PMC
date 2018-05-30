#include "TB.h"
#include <bitset>

void cortex::cortex_TB()
{
    enable_all_pid();
    disable_all_pid();
    read_pid();
    custom_pid();
    read_pid();

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

void cortex::send_cmd_TB(int W, int adr, int data){

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    sc_time delay = sc_time(10, SC_NS);

    tlm::tlm_command cmd = static_cast<tlm::tlm_command>(W);

    trans->set_command( cmd );
    trans->set_address( adr );
    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
    trans->set_data_length( 4 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

    cout << "--------------------- EMISSION --------------------" << endl;
    cout << "envoi commande : "  << cmd <<endl;
    cout << "envoi address : " << hex << adr << endl;
    cout << "envoi data : " << data << endl;
    cout << "---------------------------------------------------" << endl;

    socket->b_transport(*trans, delay);

    if ( trans->is_response_error() )
             cout << "ERROR" << endl << endl << endl;
}

void cortex::enable_all_pid(){
    int W = 1;
    int adr = 0x10;
    int data = 0x081E7800;

    cout << endl << endl << "ENABLE ALL PID" << endl;
    send_cmd_TB(W, adr, data);
}

void cortex::disable_all_pid(){
    int W = 1;
    int adr = 0x14;
    int data = 0x081E7800;

    cout << "DISABLE ALL PID" << endl;
    send_cmd_TB(W, adr, data);
}

void cortex::read_pid(){
    int W = 0;
    int adr = 0x18;
    int data = 0x081E7800;

    cout << "READ STATUS PID" << endl;
    send_cmd_TB(W, adr, data);
}

void cortex::custom_pid(){


    int W = 1;

    bool UART0      = true;
    bool UART1      = true;
    bool UART2      = true;
    bool UART3      = false;
    bool TIMER      = true;
    bool GPIO_A     = true;
    bool GPIO_B     = false;
    bool GPIO_C     = true;
    bool GPIO_D     = true;
    
    
    int MASK_UART0  = 0x00020000;
    int MASK_UART1  = 0x00040000;
    int MASK_UART2  = 0x00080000;
    int MASK_UART3  = 0x00100000;
    int MASK_TIMER  = 0x08000000;
    int MASK_GPIO_A = 0x00000800;
    int MASK_GPIO_B = 0x00001000;
    int MASK_GPIO_C = 0x00002000;
    int MASK_GPIO_D = 0x00004000;
    

    int data_enable = 0x00000000;

    int adr_enable = 0x10;
    int adr_disable = 0x14;
    
    if(UART0){
        data_enable = data_enable | MASK_UART0;
    }
 
    if(UART1){
        data_enable = data_enable | MASK_UART1;
    }

    if(UART2){
        data_enable = data_enable | MASK_UART2;
    }

    if(UART3){
        data_enable = data_enable | MASK_UART3;
    }

    if(TIMER){
        data_enable = data_enable | MASK_TIMER;
    }

    if(GPIO_A){
        data_enable = data_enable | MASK_GPIO_A;
    }

    if(GPIO_B){
        data_enable = data_enable | MASK_GPIO_B;
    }

    if(GPIO_C){
        data_enable = data_enable | MASK_GPIO_C;
    }

    if(GPIO_D){
        data_enable = data_enable | MASK_GPIO_D;
    }

    cout << endl << endl << "CUSTOM PID" << endl;
    send_cmd_TB(W,adr_enable, data_enable);
    send_cmd_TB(W,adr_disable, ~data_enable);
}
