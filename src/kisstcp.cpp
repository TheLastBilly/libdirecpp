// libdirecpp - kisstcp.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. 

#include "include/kisstcp.hpp"
#include "include/ax25.hpp"
#include "include/kiss.hpp"

namespace KissTcp{

    Kiss::Kiss kiss;

    ConnectTcp::ConnectTcp connect_tcp;

    //Class constructors
    /*------------------------------------------------------------------------------------*/
    KissTcp::KissTcp( void ){ }

    KissTcp::KissTcp( const char * s_ip, int s_port ){
        //Set socket connection as TCP and with IPv4
        connect_tcp = ConnectTcp::ConnectTcp( s_ip, s_port );
    }

    //Public functions
    /*------------------------------------------------------------------------------------*/

    //Starts socket
    int KissTcp::init( void ){
        return connect_tcp.init();
    }

    //Ends session
    void KissTcp::end( void ){
        return connect_tcp.end();
    }

    //Sends 8 bit array (a package) formated as KISS command
    uint8_t KissTcp::send_arr( uint8_t * raw_pkg, int pkg_size ){
        int size = 0;
        uint8_t *pkg = kiss.send_arr(raw_pkg, pkg_size, &size);
        return connect_tcp.command_send(pkg, size);
    }

    //Gets an AX25 frame as byte array
    int KissTcp::get_arr( uint8_t ** raw_pkg ){

        uint8_t buffer[PKG_MAX];
        bzero( buffer, PKG_MAX );

        if( connect_tcp.command_read( buffer, PKG_MAX ) == -1){
            return -1;
        }

        return kiss.get_arr(raw_pkg, buffer);

    }

    bool KissTcp::is_connected(){
        return connect_tcp.is_connected();
    }
}
