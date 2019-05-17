#ifndef CONNECT_TCP_HPP
#define CONNECT_TCP_HPP

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>

//Direwolf server default ip and port (KISS)
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8001
//Warning: Do not decrease the size by lower than (MAX_ADDR * MAX_ADDR_SIZE + 4) as it may cause errors
#define TIME_OUT 10

namespace ConnectTcp{
    class ConnectTcp{

        struct sockaddr_in serveraddr;
        int sckt;

    public:

        ConnectTcp( void );
        ConnectTcp( const char * server_ip, int server_port );
        uint8_t command_send( uint8_t * cmd, int size );
        void command_send( uint8_t * buffer );
        int command_read( uint8_t * buffer, int size );
        uint16_t get_arr( uint8_t ** raw_pkg );
        bool is_connected( void );
        int init( void );
        void end( void );
    };
}

#endif
