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
    con_set.server_ip = EXAMPLE_IP;
    con_set.server_port = EXAMPLE_PORT;
    DireCpp::DireCpp direcpp( con_set );

    //Initialize direcpp with the wanted calls, and check if
    //connection is stable
    if(!direcpp.init(EXAMPLE_CALLSIGN, EXAMPLE_CALLSIGN)){
        bool good = false;
        //Create an empty packet
        AX25::aprs_packet packet = {};

        //Whenever you get something, stop
        while(!direcpp.receive(&packet)){ }

        //Get packet's info as a string and print it
        std::cout << direcpp.get_info_str(packet) << std::endl;
    }else{
        //If something went wrong, let me know
        std::cout << "Connection error" << std::endl;
    }

    //Terminate direcpp session
    direcpp.end();
    return 0;

}
