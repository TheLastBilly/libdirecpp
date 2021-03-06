// libdirecpp - direcpp.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.


#include "direcpp.hpp"

namespace DireCpp{

    KissSerial::KissSerial * kiss_serial = nullptr;
    KissTcp::KissTcp * kisstcp = nullptr;

    AX25::AX25 ax25;
    //Class constructors
    /*------------------------------------------------------------------------------------*/
    DireCpp::DireCpp( void ):
    connection_type(-1) { }
    DireCpp::DireCpp( connection_settings con_set ):
    connection_type( con_set.type ){
        switch( connection_type ){
            case SERIAL_KISS:
                kiss_serial = new KissSerial::KissSerial(con_set.serial_port, con_set.serial_baud);
                break;
            case TCP_KISS:
                kisstcp = new KissTcp::KissTcp(con_set.server_ip, con_set.server_port);
                break;
            default:
                connection_type = 1;
                kisstcp = new KissTcp::KissTcp(SERVER_ADDR, SERVER_PORT);
        }
    }

    //Public functions
    /*------------------------------------------------------------------------------------*/

    //Sends an array of bytes over AX25
    int DireCpp::transmit( uint8_t * payload, uint32_t size ){
        uint16_t raw_frame_size = ax25.raw_frame_size( size );
        uint8_t buffer[ raw_frame_size ];
        ax25.make_raw_packet( orig_addr, dest_addr, payload, size, buffer );
        if(connection_type == SERIAL_KISS)
            return kiss_serial->send_arr( buffer, raw_frame_size );
        else if(connection_type == TCP_KISS)
            return kisstcp->send_arr( buffer, raw_frame_size );
        else
            return kisstcp->send_arr( buffer, raw_frame_size );
    }


    //Receives and array of bytes (array size determined by return value).
    //The buffer where the initial bytes will be store need to be of size MAX_INFO
    bool DireCpp::receive( AX25::aprs_packet *pckt ){
        uint8_t * buffer;
        int size = 0;
        if(connection_type == SERIAL_KISS)
            size = kiss_serial->get_arr( &buffer );
        else if(connection_type == TCP_KISS)
            size = kisstcp->get_arr( &buffer );
        else
            size = kisstcp->get_arr( &buffer );
        //std::cout << "DireCpp packet size " << size << endl;
        AX25::aprs_packet packet = { };
        if( size < 0 ){
            return false;
        }
        else{
            packet = ax25.packet_from_raw( buffer, size );
            //std::cout << "DireCpp packet size " << packet.info_size << endl;
            *pckt = packet;
        }

        return true;
    }

    bool DireCpp::receive_by_call( AX25::aprs_packet *pckt ){
        AX25::aprs_packet packet = {};
        if(!DireCpp::receive(&packet))
            return false;
        bool confirm = true;
        for(uint16_t i = 0; i < MAX_ADDR_SIZE -1 && confirm; i++)
            confirm = packet.call_dest[i] == orig_addr[i];
        if(!confirm)
            return false;
        *pckt = packet;
        return true;
    }

    int DireCpp::send_string( std::string msg_str ){
        uint32_t str_size = msg_str.length();
        const char * msg = msg_str.c_str();
        uint8_t buffer[ str_size ];
        for( uint16_t i = 0; i < str_size+1; i++ ){
            buffer[i] = msg[i];
            buffer[i] = buffer[i] == 0x00 ? 0x20 : buffer[i];
        }
        return DireCpp::transmit( buffer, str_size );
    }

    /*int DireCpp::init( const char * source, const char * destination, string ip, int port ){
        DireCpp::change_addr( source, destination );
        connector = connector::connector( ip.c_str(), port );
        return connector->init( );
    }*/

    int DireCpp::init( std::string source , std::string destination ){
        DireCpp::change_addr( source, destination );
        if(connection_type == SERIAL_KISS)
            return kiss_serial->init();
        else if(connection_type == TCP_KISS)
            return kisstcp->init();
        else
            return kisstcp->init();
    }

    int DireCpp::init( void ){
        DireCpp::change_addr( NO_CALL, NO_CALL );
        if(connection_type == SERIAL_KISS)
            return kiss_serial->init();
        else if(connection_type == TCP_KISS)
            return kisstcp->init();
        else
            return kisstcp->init();
    }

    bool DireCpp::is_connected(){
        if(connection_type == SERIAL_KISS)
            return kiss_serial->is_connected();
        else if(connection_type == TCP_KISS)
            return kisstcp->is_connected();
        else
            return kisstcp->is_connected();
    }

    void DireCpp::change_addr( std::string source , std::string destination ){
        DireCpp::str_uppr(source);
        DireCpp::str_uppr(destination);
        ax25.ax25_addr_conv( source.c_str(), orig_addr, true, 0 );
        ax25.ax25_addr_conv( destination.c_str(), dest_addr, false, 0 );
        rx_call = destination;
        tx_call = source;
    }

    void DireCpp::end( void ){
        if(connection_type == SERIAL_KISS)
            return kiss_serial->end();
        else if(connection_type == TCP_KISS)
            return kisstcp->end();
        else
            return kisstcp->end();
    }
    DireCpp::~DireCpp( void ){
        if(kiss_serial != nullptr){
            //std::cout << "Here's the problem 1" << std::endl;
            delete(kiss_serial);
            kiss_serial = nullptr;
        }
        if(kisstcp != nullptr){
            //std::cout << "Here's the problem 2" << std::endl;
            delete(kisstcp);
            kisstcp = nullptr;
        }
        if(kisstcp != nullptr){
            //std::cout << "Here's the problem 3" << std::endl;
            delete(kisstcp);
            kisstcp = nullptr;
        }
    }

    std::string DireCpp::get_info_str(AX25::aprs_packet packet){
        char info_raw[packet.info_size];
        memcpy(info_raw, packet.info, packet.info_size -1);
        return std::string( info_raw );
    }

    //Private functions
    /*------------------------------------------------------------------------------------*/

    void DireCpp::str_uppr(std::string& lower_case){
        for(unsigned int i=0;i<lower_case.length();i++){
            lower_case[i] = toupper(lower_case[i]);
        }
    }

}
