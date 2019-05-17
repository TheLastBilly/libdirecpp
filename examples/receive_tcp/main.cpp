#include <iostream>
#include <termios.h>
#include "../../src/include/direcpp.hpp"


int main( int argc, char ** argv ){

    //Start direcpp as TCP
    DireCpp::DireCpp direcpp("127.0.0.1", 8001, TCP_KISS);

    //Initialize direcpp with the wanted calls
    int direcpp_connection = direcpp.init("nocall", "nocall");
    if(!direcpp_connection){
        bool good = false;
        AX25::ax25_packet packet ={};

        while(!good){
            packet = direcpp.receive();
            if(packet.size > -1)
                good = true;
        }

        std::cout << direcpp.get_info_str(packet) << std::endl;
    }else{
        std::cout << "Connection error" << std::endl;
    }

    direcpp.end();
    return 0;

}