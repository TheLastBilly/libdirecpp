// libdirecpp - ax25.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "include/ax25.hpp"

#define PID 0x03
#define CONTROL 0xf0

namespace AX25{


    //Class constructor
    /*------------------------------------------------------------------------------------*/
    AX25::AX25( void ):
    control(CONTROL),
    pid(PID){ }
    AX25::AX25( uint8_t ctl, uint8_t p ):
    control(ctl),
    pid(p){}

    //Public functions
    /*------------------------------------------------------------------------------------*/
    //Generates AX25 packet as a byte (uint8_t * ) array

    uint8_t AX25::build_ssid( uint8_t id, bool source ){
        uint8_t ssid = id << 1;
        ssid |= 0b01100000;
        ssid |= source << 7;
        ssid |= source;
        return ssid;
    }

    void AX25::make_raw_packet( uint8_t * addr_orig, uint8_t * addr_dest,  uint8_t * data, uint32_t data_size, uint8_t * raw_frame ){

        //Verify data integrity
        if(data_size > MAX_INFO){
            //debug
            exit(0);
        }

        //Create frame buffer
        uint16_t frame_size = AX25::raw_frame_size(data_size);
        uint8_t frame[ frame_size ];

        //Format buffer
        /*----------------------------------------------------------------*/
        uint32_t frame_pos = 0;
        memcpy( &frame[0], addr_dest, MAX_ADDR_SIZE );
        frame_pos = MAX_ADDR_SIZE;

        memcpy( frame + frame_pos , addr_orig, MAX_ADDR_SIZE );
        frame_pos += MAX_ADDR_SIZE;

        frame[ frame_pos ] = pid;
        frame_pos += 1;

        frame[ frame_pos ] = control;
        frame_pos += 1;

        memcpy( frame + frame_pos , data, data_size );
        /*----------------------------------------------------------------*/

        //Copy frame to raw_frame
        frame_pos += data_size;
        memcpy( raw_frame, frame, frame_size );

    }

    //Returns expected raw frame size
    uint16_t AX25::raw_frame_size( int size ){
        return ((MAX_ADDR_SIZE) * 2 + 2 + size);
    }

    //Returns a ax25_paclet structure based on raw AX25 frame
    aprs_packet AX25::packet_from_raw( uint8_t * raw_packet, uint16_t packet_size ){

        aprs_packet entry = {};
        //If there's not enough space for at least two addresses plus the necessary flags
        if( packet_size < (2 * (MAX_ADDR_SIZE)) + 2 ){
            //Error/Debug
            return entry;
        }
        uint8_t addr_count = 1;
        while( addr_count < MAX_ADDR ){
            //The last SSID octect (A.K.A: the one containing the last address) is the only one set to 1
            if( raw_packet[ ((addr_count) * (MAX_ADDR_SIZE)) - 1] & 0x01 == 0x01 ) break;
            addr_count++;
        }
        if( addr_count < 2 ){
            //Error/Debug
            return entry;
        }
        uint16_t index = 0;

        memcpy( entry.call_dest, raw_packet + index , MAX_ADDR_SIZE );
        index += MAX_ADDR_SIZE;

        memcpy( entry.call_orig, raw_packet + index, MAX_ADDR_SIZE );
        index += MAX_ADDR_SIZE;
        uint8_t digi_count = 0;
        if( !(raw_packet[index - 1] & 0b0000001) ){
            for( ; digi_count < addr_count - 2 && !(raw_packet[index + digi_count * MAX_ADDR_SIZE ] & 0b0000001); digi_count++ ){
                memcpy( entry.digi + (digi_count * (MAX_ADDR_SIZE)), raw_packet + index + (digi_count * (MAX_ADDR_SIZE)), MAX_ADDR_SIZE );
            }
        }
        memcpy( entry.info, raw_packet + index, packet_size - index);
        AX25::print_arr(raw_packet, packet_size);
        entry.info_size = packet_size;
        entry.digi_count = digi_count;
        entry.size = index;

        return entry;

    }

    void AX25::ax25_addr_conv( const char * call, uint8_t * arr, bool source, uint8_t num ){
        uint8_t buffer[ MAX_ADDR_SIZE ];
        for( uint8_t i = 0; i < MAX_ADDR_SIZE - 1; i++ ){
            buffer[i] = call[i] << 1;
        }
        buffer[MAX_ADDR_SIZE - 1] = AX25::build_ssid( num, source );
        memcpy( arr, buffer, MAX_ADDR_SIZE );
    }

    //(For debbuging) Prints array values
    void AX25::print_arr( uint8_t *ptr, int size ){
        for(int i = 0; i < size; i++){
            printf("%02X ", ptr[i]);
        }
        printf("\n");
    }

}
