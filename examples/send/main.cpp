#include <iostream>
#include <termios.h>
#include "../../src/include/direcpp.hpp"

#define EXAMPLE_IP "127.0.0.1"
#define EXAMPLE_PORT 8001

#define EXAMPLE_CALLSIGN "nocall"

int main( int argc, char ** argv ){

    //Create direcpp object and start it as TCP
    DireCpp::connection_settings con_set = {};
    con_set.type = TCP_KISS;
    con_set.ip = EXAMPLE_IP;
    con_set.net_port = EXAMPLE_PORT;
    
    DireCpp::DireCpp direcpp(con_set);

    //Initialize direcpp with the wanted calls, and check if
    //connection is stable
    if(!direcpp.init("VE2JMN", "APX211")){
        //Send string over direcpp
        direcpp.send_string("Test packet, VE2JMN");
    }else{
        //If something went wrong, let me know
        std::cout << "Connection error" << std::endl;
    }

    //Terminate direcpp session
    direcpp.end();
    return 0;

}
