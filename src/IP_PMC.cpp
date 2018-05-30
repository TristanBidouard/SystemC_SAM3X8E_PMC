#include "IP_PMC.h"

void IP_PMC::pmc_constructor()
{

}

void IP_PMC::b_transport( tlm::tlm_generic_payload& trans, sc_time& delay)
{
    int indice = 1;
    int result;
    int retour;
    int data_in;
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    int offset = adr;
    cout << "Offset = " << offset << endl;

    memcpy(&data_in, ptr, len);

    if(cmd) {
        if (adr == 0x10) { 
                for (int i = 0 ; i < 31 ; i++) {
                    indice = indice << 1;
                    result = data_in & indice;
                    switch(result) {
		                case 0x00020000 : 
                            socket_UART_o[0]->enable();       // Activation CLK_EN UART0
                            break;
		                case 0x00040000 : 
                            socket_UART_o[1]->enable();       // Activation CLK_EN UART1
                            break;
		                case 0x00080000 : socket_UART_o[2]->enable();       // Activation CLK_EN UART2
                            break;
		                case 0x00100000 : socket_UART_o[3]->enable();       // Activation CLK_EN UART3
                            break;
		                case 0x08000000 : enable_timer();                   // Activation CLK_EN TIMER
                            break;
		                case 0x00000800 : socket_GPIO_o[0]->enable();       // Activation CLK_EN GPIO_A
                            break;
                        case 0x00001000 : socket_GPIO_o[1]->enable();       // Activation CLK_EN GPIO_B
                            break;
                        case 0x00002000 : socket_GPIO_o[2]->enable();       // Activation CLK_EN GPIO_C
                            break;
                        case 0x00004000 : socket_GPIO_o[3]->enable();       // Activation CLK_EN GPIO_D
                            break;
	                }
                }
                retour =  mem[0x18/4].write(data_in); // Mettre à jour le registre de status
        } else if (adr == 0x14) {
                for (int i = 0 ; i < 32 ; i++) {
                    indice = indice << 1;
                    result = data_in & indice;
                    switch(result) {
		                case 0x00020000 : socket_UART_o[0]->disable();
                            break;
		                case 0x00040000 : socket_UART_o[1]->disable();
                            break;  
		                case 0x00080000 : socket_UART_o[2]->disable();
                            break;    
		                case 0x00100000 : socket_UART_o[3]->disable();
                            break;     
		                case 0x08000000 : disable_timer();
                            break;                
		                case 0x00000800 : socket_GPIO_o[0]->disable();
                            break;    
                        case 0x00001000 : socket_GPIO_o[1]->disable();
                            break;   
                        case 0x00002000 : socket_GPIO_o[2]->disable();
                            break;      
                        case 0x00004000 : socket_GPIO_o[3]->disable();
                            break;
	                }
                }
            retour =  mem[0x18/4].write(data_in); // Mettre à jour le registre de status
        }
        /* Mettre à jour le registre en question */
        retour =  mem[offset/4].write(data_in);
        /*mem[offset/4].write((int)(*ptr));*/
    } else {
        /* Lire le registre en question */
        retour = mem[offset/4].read((int*)ptr);
        /**ptr = mem[offset/4].read();*/
    }

    trans.set_response_status((tlm::tlm_response_status)retour);
}

void IP_PMC::memory_init(){
    cout << "Initialisation de la mémoire" << endl;
    for(int i = 0; i <= 67; i++){
        mem[i].adr = i;
        mem[i].data = round(rand()*1000);
    }
    mem[0].type = "W";
    mem[1].type = "W";
    mem[2].type = "R";
    mem[3].type = "X";
    mem[4].type = "W";
    mem[5].type = "W";
    mem[6].type = "R";
    mem[7].type = "A";
    mem[8].type = "A";
    mem[9].type = "R";
    mem[10].type = "A";
    mem[11].type = "X";
    mem[12].type = "A";
    mem[13].type = "X";
    mem[14].type = "A";
    mem[15].type = "X";
    mem[16].type = "A";
    mem[17].type = "A";
    mem[18].type = "A";
    mem[19].type = "X";
    mem[20].type = "X";
    mem[21].type = "X";
    mem[22].type = "X";
    mem[23].type = "X";
    mem[24].type = "W";
    mem[25].type = "W";
    mem[26].type = "R";
    mem[27].type = "R";
    mem[28].type = "A";
    mem[29].type = "A";
    mem[30].type = "W"; 

    mem[31].type = "X";
    mem[32].type = "X";
    mem[33].type = "X";
    mem[34].type = "X";
    mem[35].type = "X";
    mem[36].type = "X";
    mem[37].type = "X";
    mem[38].type = "X";
    mem[39].type = "X";
    mem[40].type = "X";
    mem[41].type = "X";
    mem[42].type = "X";
    mem[43].type = "X";
    mem[44].type = "X";
    mem[45].type = "X";
    mem[46].type = "X";
    mem[47].type = "X";
    mem[48].type = "X";
    mem[49].type = "X";
    mem[50].type = "X";
    mem[51].type = "X";
    mem[52].type = "X";
    mem[53].type = "X";
    mem[54].type = "X";
    mem[55].type = "X";
    mem[56].type = "X";
    mem[57].type = "A";
    mem[58].type = "R";
    mem[59].type = "X";
    mem[60].type = "X";
    mem[61].type = "X";
    mem[62].type = "X";
    mem[63].type = "X";
    mem[64].type = "W";
    mem[65].type = "W";
    mem[66].type = "R";
    mem[67].type = "A"; 
}

void IP_PMC::enable_timer() {
    ce_timer = 1;

    sc_time delay = sc_time(10, SC_NS);

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    trans->set_command(cmd);
    trans->set_address(0);
    trans->set_data_ptr(&ce_timer);
    trans->set_data_length(1);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    cout << "Enable timer" << endl;

    socket_timer->b_transport(*trans, delay);

     if (trans->is_response_error())
        cout << "Erreur dans la réponse" << endl;
}

void IP_PMC::disable_timer() {
    sc_time delay = sc_time(10, SC_NS);

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    ce_timer = 0;

    trans->set_command( cmd );
    trans->set_address( 0 );
    trans->set_data_ptr(&ce_timer);
    trans->set_data_length( 1 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

    cout << "Disable timer" << endl;

    socket_timer->b_transport(*trans, delay);

     if ( trans->is_response_error() )
        cout << "Erreur dans la réponse" << endl;
}


void socket_PMC::enable() {
    ce_UART = true;

    sc_time delay = sc_time(10, SC_NS);

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    trans->set_command(cmd);
    trans->set_address( 0 );
    trans->set_data_ptr((unsigned char*)&ce_UART);
    trans->set_data_length(1);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    socket->b_transport(*trans, delay);

     if (trans->is_response_error())
        cout << "Erreur dans la réponse" << endl;
}

void socket_PMC::disable() {
    ce_UART = false;

    sc_time delay = sc_time(10, SC_NS);

    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    trans->set_command(cmd);
    trans->set_address( 0 );
    trans->set_data_ptr((unsigned char*)&ce_UART);
    trans->set_data_length(1);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    socket->b_transport(*trans, delay);

     if (trans->is_response_error())
        cout << "Erreur dans la réponse" << endl;
}

socket_PMC::socket_PMC(string nom) : socket("socket_UART") {
    name = nom;
}

int memory::read(int* valeur_lu) {
    if(type == "R" || type == "A"){
        cout << "On lit la valeur '" << hex << data << "' à l'adresse " << dec << adr << " qui a le status " << type << endl << endl << endl << endl;
        *valeur_lu = data;
        return (tlm::TLM_OK_RESPONSE);
    }else{
        cout << "Le status '" << type << "' de l'adresse " << dec << adr << " n'autorise pas la lecture." << endl << endl << endl << endl;
        return (tlm::TLM_COMMAND_ERROR_RESPONSE);
    }
}

int memory::write(int data_in){
    /* Vérifier que le registre est W */
    if(type == "W" || type == "A"){
        data = data_in;
        cout << "On écrit la donnée '" << hex << data << "' à l'adresse " << dec << adr << " qui a le status " << type << endl << endl << endl << endl;
        return (tlm::TLM_OK_RESPONSE);
    }else{
        cout << "Le status '" << type << "' de l'adresse " << dec << adr << " n'autorise pas la lecture." << endl << endl << endl << endl;
        return (tlm::TLM_COMMAND_ERROR_RESPONSE);
    }           
}

