#ifndef KISS_HPP
#define KISS_HPP

#include "ax25.hpp"

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <stdio.h>

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

#define PKG_MAX 1024

using namespace std;

namespace Kiss{
    class Kiss{

        public:

            Kiss( );
            uint8_t * send_arr( uint8_t * raw_pkg, int pkg_size, int * size );
            uint16_t get_arr( uint8_t ** raw_pkg, uint8_t buffer[PKG_MAX]);

    };
}

#endif
