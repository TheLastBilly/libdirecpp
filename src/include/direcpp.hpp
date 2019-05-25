// libdirecpp - direcpp.hpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. 

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

#define TCP_CONNECTION_ERROR 0
#define SERIAL_CONNECTION_ERROR 1

using namespace std;

namespace DireCpp{

    class DireCpp{

        uint8_t control;
        uint8_t pid;

        uint8_t orig_addr[ MAX_ADDR_SIZE ];
        uint8_t dest_addr[ MAX_ADDR_SIZE ];

        public:

            DireCpp( void );
            DireCpp( const char * addr, int param, short t );
            ~DireCpp( void );
            void end( void );
            int init( void );
            int init( std::string source , std::string destination );
            //int init( const char * source, const char * destination, string ip, int port );
            int transmit( uint8_t * payload, uint32_t size );
            uint8_t set_ssid( uint8_t num, bool source );
            bool receive( AX25::aprs_packet *pckt );
            bool receive_by_call( AX25::aprs_packet *pckt );
            int send_string( std::string msg_str );
            void change_addr( std::string source , std::string destination );
            uint16_t get_direcpp_msg( uint8_t * ptr );
            bool is_connected();
            std::string get_info_str(AX25::aprs_packet packet);

            std::string rx_call, tx_call;
            int errno;

        private:
            int connection_type;
            void str_uppr(string& lower_case);
    };
}

#endif
