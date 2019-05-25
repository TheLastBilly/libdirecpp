#include <iostream>
#include <termios.h>
#include "../../src/include/direcpp.hpp"

#define EXAMPLE_IP "127.0.0.1"
#define EXAMPLE_PORT 8001

#define EXAMPLE_CALLSIGN "nocall"

int main( int argc, char ** argv ){

    //Create direcpp object and start it as TCP
    DireCpp::DireCpp direcpp(EXAMPLE_IP, EXAMPLE_PORT, TCP_KISS);

    //Initialize direcpp with the wanted calls, and check if 
    //connection is stable
    if(!direcpp.init("VE2JMN", "APX211")){
        //Send string over direcpp
        direcpp.send_string("Hello World!");
    }else{
        //If something went wrong, let me know
        std::cout << "Connection error" << std::endl;
    }

    //Terminate direcpp session
    direcpp.end();
    return 0;

}