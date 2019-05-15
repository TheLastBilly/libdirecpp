#include "../include/kiss_serial.hpp"
#include "../include/ax25.hpp"
#include "../include/kiss.hpp"

namespace KissSerial{

    Kiss::Kiss kiss;

    ConnectSerial::ConnectSerial connect_serial;

    //Class constructors
    /*------------------------------------------------------------------------------------*/
    KissSerial::KissSerial( void ){ }

    KissSerial::KissSerial( const char * s_ip, int s_port ){
        //Set socket connection as Serial and with IPv4
        connect_serial = ConnectSerial::ConnectSerial( s_ip, s_port );
    }

    //Public functions
    /*------------------------------------------------------------------------------------*/

    //Starts socket
    int KissSerial::init( void ){
        connect_serial.init();
    }

    //Ends session
    void KissSerial::end( void ){
        connect_serial.end();
    }

    //Sends 8 bit array (a package) formated as KISS command
    uint8_t KissSerial::send_arr( uint8_t * raw_pkg, int pkg_size ){
        int size = 0;
        uint8_t *pkg = kiss.send_arr(raw_pkg, pkg_size, &size);
        return connect_serial.command_send(pkg, size);
    }

    //Gets an AX25 frame as byte array
    uint16_t KissSerial::get_arr( uint8_t ** raw_pkg ){

        uint8_t buffer[PKG_MAX];
        bzero( buffer, PKG_MAX );

        if( connect_serial.command_read( buffer, PKG_MAX ) == -1){
            return -1;
        }

        return kiss.get_arr(raw_pkg, buffer);

    }

    bool KissSerial::is_connected(){
        return connect_serial.is_connected();
    }
}