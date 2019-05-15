#ifndef KISSTCP_HPP
#define KISSTCP_HPP

#include "connect_tcp.hpp"
#include "kiss.hpp"

//KISS special characters
#define FEND 0xC0
#define FESC 0xDB
#define TFEND 0XDC
#define TFESC 0XDD

//KISS commands
#define D_FRAME 0X00
#define TX_DELAY 0X01
#define P 0x02
#define TX_TAIL 0x04
#define F_DUPLEX 0x05
#define SET_HW 0X06
#define EXIT 0XFF

using namespace std;

namespace KissTcp{
    class KissTcp{

        struct sockaddr_in serveraddr;
        int sckt;

        private:

            uint8_t command_send( uint8_t cmd[], int size );

        public:

            KissTcp( void );
            KissTcp( const char * server_ip, int server_port );
            int init( void );
            void end( void );
            uint8_t send_arr( uint8_t * raw_pkg, int pkg_size );
            int get_arr( uint8_t ** raw_pkg );
            bool is_connected();

    };
}

#endif
