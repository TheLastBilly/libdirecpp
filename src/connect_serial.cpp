// libdirecpp - connect_serial.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "connect_serial.hpp"

namespace ConnectSerial{

    ConnectSerial::ConnectSerial(){}

    ConnectSerial::ConnectSerial( const char * serial_dev, int bd_rate ):
    baud_rate( bd_rate ){
        serial_port = open( serial_dev, O_RDWR);
    }

    int ConnectSerial::init( void ){
        if(serial_port == -1)
            return 1;
        memset(&tty, 0, sizeof(tty));
        if(tcgetattr(serial_port, &tty) != 0) {
            //printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }

        //Taken from https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

        tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
        tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
        tty.c_cflag |= CS8; // 8 bits per byte (most common)
        tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
        tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

        tty.c_lflag &= ~ICANON;
        tty.c_lflag &= ~ECHO; // Disable echo
        tty.c_lflag &= ~ECHOE; // Disable erasure
        tty.c_lflag &= ~ECHONL; // Disable new-line echo
        tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

        tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
        tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

        //tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
        tty.c_cc[VMIN] = 0;

        // Set in/out baud rate to be 9600
        cfsetispeed(&tty, baud_rate);
        cfsetospeed(&tty, baud_rate);

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            return 1;
            //printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        }
        return 0;
    }

    int ConnectSerial::command_send( uint8_t cmd[], int size ){
        if(cmd == nullptr)
            return -1;
        else{
            uint8_t arr[size];
            memcpy(arr, cmd, size);
            delete(cmd);
            return write( serial_port, arr, size );
        }
    }

    int ConnectSerial::command_read( uint8_t * buffer, int size ){
        return read (serial_port, buffer, size);
    }

    bool ConnectSerial::is_connected( void ){
        return serial_port != -1;
    }

    void ConnectSerial::end( void ){
        close(serial_port);
    }

}
