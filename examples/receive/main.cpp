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
    if(!direcpp.init(EXAMPLE_CALLSIGN, EXAMPLE_CALLSIGN)){
        bool good = false;
        //Create an empty packet 
        AX25::ax25_packet packet = {};

        //Whenever you get something, stop
        while(!good){
            //Get packet info
            packet = direcpp.receive();
            if(packet.size > -1)
                good = true;
        }

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