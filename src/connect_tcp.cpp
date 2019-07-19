// libdirecpp - connect_tcp.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "connect_tcp.hpp"

namespace ConnectTcp{

    const char * server_ip = SERVER_ADDR;
    int server_port = SERVER_PORT;
    bool socket_set = false;

    ConnectTcp::ConnectTcp( void ){};

    ConnectTcp::ConnectTcp( const char * s_ip, int s_port ){
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        sckt = socket(AF_INET, SOCK_STREAM, 0);

        socket_set = true;
        //Set server's IP address and port
        server_ip = s_ip;
        server_port = s_port;
    }

    int ConnectTcp::init( void ){
        if( !socket_set ){
            memset(&serveraddr, 0, sizeof(serveraddr));
            serveraddr.sin_family = AF_INET;
            sckt = socket(AF_INET, SOCK_STREAM, 0);
        }

        //Set defaults server's IP address and port
        serveraddr.sin_addr.s_addr = inet_addr(server_ip);
        serveraddr.sin_port = htons(server_port);

        struct timeval tv;
        tv.tv_usec = TIME_OUT;
        tv.tv_sec = 0;
        if ( setsockopt(sckt, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) != 0 ){
            //debug
            return 1;
        }
        if ( connect(sckt, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0 ){
            return 1;
        } //else printf("Connected to server %s \n", SERVER_ADDR);
        fcntl(sckt, F_SETFL, O_NONBLOCK);
        return 0;

    }

    void ConnectTcp::end( void ){
        //End KISS (TCP) session
        close(sckt);
        socket_set = false;
    }

    int ConnectTcp::command_read( uint8_t * buffer, int size ){
        return read( sckt, buffer, size );
    }

    //Write raw byte array over KISS
    int ConnectTcp::command_send( uint8_t * cmd, int size ){
        if(cmd == nullptr)
            return -1;
        else{
            uint8_t arr[size];
            memcpy(arr, cmd, size);
            delete(cmd);
            return send(sckt, arr, size, 0);
        }
    }

    bool ConnectTcp::is_connected( void ){
        int error_code;
        socklen_t error_code_size = sizeof(error_code);
        getsockopt(sckt, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
        if( error_code != -1 ){
            return true;
        }
        return false;
    }
}
