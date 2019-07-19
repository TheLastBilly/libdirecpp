// libdirecpp - kiss_serial.hpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. 

#ifndef KISSSerial_HPP
#define KISSSerial_HPP

#include "connect_serial.hpp"
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

namespace KissSerial{
    class KissSerial{

        private:

            uint8_t command_send( uint8_t cmd[], int size );

        public:

            KissSerial( void );
            KissSerial( const char * s_ip, int s_port );
            int init( void );
            void end( void );
            int send_arr( uint8_t * raw_pkg, int pkg_size );
            int get_arr( uint8_t ** raw_pkg );
            bool is_connected();

    };
}

#endif
