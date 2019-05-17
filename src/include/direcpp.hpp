#ifndef DIRE_HPP
#define DIRE_HPP

#include "kisstcp.hpp"
#include "kiss_serial.hpp"
#include "ax25.hpp"

//Default PID and
#define PID_D NO_LAYER
#define CONTROL_D 0x03
#define NO_CALL "NO CALL"

#define SERIAL_KISS 0
#define TCP_KISS 1

using namespace std;

namespace DireCpp{

    class DireCpp{

        uint8_t control;
        uint8_t pid;

        uint8_t orig_addr[ MAX_ADDR_SIZE ];
        uint8_t dest_addr[ MAX_ADDR_SIZE ];

        public:

            DireCpp( void );
            DireCpp( std::string addr, int param, short t );
            ~DireCpp( void );
            void end( void );
            int init( void );
            int init( std::string source , std::string destination );
            //int init( const char * source, const char * destination, string ip, int port );
            uint8_t transmit( uint8_t * payload, uint32_t size );
            uint8_t set_ssid( uint8_t num, bool source );
            int receive( uint8_t * store );
            int receive_by_call( uint8_t * store );
            uint8_t send_string( std::string msg_str );
            void change_addr( std::string source , std::string destination );
            uint16_t get_direcpp_msg( uint8_t * ptr );
            bool is_connected();

            std::string rx_call, tx_call;

        private:
            int connection_type;
            void str_uppr(string& lower_case);
    };
}

#endif
