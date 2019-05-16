#include "kiss.hpp"
#include "ax25.hpp"

namespace Kiss{
    uint8_t *f_pkg = nullptr;

    //Class constructors
    /*------------------------------------------------------------------------------------*/
    Kiss::Kiss( ){ }

    //Public functions
    /*------------------------------------------------------------------------------------*/

    //Sends 8 bit array (a package) formated as KISS command
    uint8_t * Kiss::send_arr( uint8_t * raw_pkg, int pkg_size, int * size ){
        //Check if pkg_raw is bigger than PKG_MAX
        if(pkg_size > PKG_MAX){
            //Debug msg
            exit(0);
        }
        //Format and send package
        uint16_t f_pkg_size = pkg_size + 3;
        f_pkg= new uint8_t[f_pkg_size];
        f_pkg[0] = f_pkg[f_pkg_size -1] = FEND;
        f_pkg[1] = D_FRAME;
        for(uint16_t i =0; i < pkg_size; i++){
            f_pkg[i + 2] = *(raw_pkg + i);
        }
        *size = f_pkg_size;
        return f_pkg;
    }

    //Gets an AX25 frame as byte array
    uint16_t Kiss::get_arr( uint8_t ** raw_pkg, uint8_t buffer[PKG_MAX]){

        uint16_t size = 0;
        uint8_t fend_found = 0;
        while( fend_found < 2 && size < PKG_MAX ){
            if( buffer[size] == FEND ){
                fend_found +=1;
            }
            size +=1;
        }
        if( size == PKG_MAX && buffer[PKG_MAX - 1] != FEND ){
            return 0;
        }else{
            //Due to FEND at the end of the buffer
            size -= 3;
        }
        uint8_t final_buffer[MAX_INFO];
        bzero( final_buffer, MAX_INFO );
        memcpy( final_buffer, buffer + 2, size );
        //std::cout << "Packet received size " << size << endl;
        *raw_pkg = &final_buffer[0];
        return size;

    }

}
