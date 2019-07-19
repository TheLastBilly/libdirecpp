// libdirecpp - ax25.hpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. 
#ifndef AX25_HPP
#define AX25_HPP

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

//AX25 PID field codes
#define ISO_X25 0x01
#define COMP_TCP 0x06
#define UNCOMP_TCP 0x07
#define SGMT_F 0x08
#define TEXTNET 0xC3
#define LQP 0xC4
#define APPT 0xCA
#define APPT_ARP 0xCB
#define ARPA_IP 0xCC
#define ARPA_AR 0xCD
#define FLEX_NET 0xCE
#define NT_ROM 0xCF
#define NO_LAYER 0xF0
#define ESCAPE 0xFF

//AX25 Frame constants
#define MAX_INFO 256
#define MAX_ADDR 10
#define MAX_ADDR_SIZE 7
#define MAX_RPTR 8

namespace AX25{

    //Contains the relevant information about a AX25 frame
    struct aprs_packet{
        uint8_t call_orig[ MAX_ADDR_SIZE ];
        uint8_t call_dest[ MAX_ADDR_SIZE ];
        uint8_t digi[ MAX_ADDR_SIZE * MAX_RPTR ];
        uint8_t digi_count;
        uint8_t info[MAX_INFO];
        uint32_t info_size;
        int size;
    };

    class AX25{
        uint8_t control, pid;
        private:

        public:
            AX25( void );
            AX25( uint8_t control, uint8_t pid );
            void make_raw_packet( uint8_t * addr_orig, uint8_t * addr_dest,  uint8_t * data, uint32_t data_size, uint8_t * raw_frame );
            uint16_t raw_frame_size( int size );
            aprs_packet packet_from_raw( uint8_t * raw_packet, uint16_t packet_size );
            uint8_t build_ssid( uint8_t id, bool source );
            void ax25_addr_conv( const char * call, uint8_t * arr, bool source, uint8_t num );
            //For debbuging
            void print_arr( uint8_t * ptr, int size );
    };

}

#endif
