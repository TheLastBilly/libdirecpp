// libdirecpp - connect_serial.hpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. 

#ifndef CONNECT_SERIAL_HPP
#define CONNECT_SERIAL_HPP

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <stdio.h>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

namespace ConnectSerial{

    class ConnectSerial{
        private:
        int serial_port, baud_rate;
        struct termios tty;

        public:
        ConnectSerial( void );
        ConnectSerial( const char * serial_dev, int bd_rate );
        int command_send( uint8_t cmd[], int size );
        int command_read( uint8_t * buffer, int size );
        bool is_connected( void );
        int init( void );
        void end( void );
    };
}

#endif