# DireCpp::DireCpp ( void )

## Return type:
`None`

## Description:
Used only to initialize a DireCpp object. If used, the connection type is set to TCP with the localhost (127.0.0.1) and port 8001 as the default network ip and port respectively.

# DireCpp::DireCpp( const char * addr, int param, short type )

## Return type:
`None`


## Description:
Used only to initialize a DireCpp object and set connection options. The connection type will be defined by the value of `type`. If set to `SERIAL_KISS` the connection type will be set to serial, and if set to `TCP_KISS` the connection type will be set to tcp. If neither of the two values is used, the connection type will be set to tcp. The server address (or serial port) is represented by the `addr` variable, and the server port (or baud rate) is represented by the `param` variable.
 
# DireCpp::init( void )

## Return type:
`int`

## Description:
Used to connect to the server with the settings specified in the class constructor. If the connection was successfully stablished, the function will return a `0`, otherwise, it'll return `-1`. It's required to succesfully call this function (or it's alternative) before any further communications done via a DireCpp object. The callsigns used for transmitting and receving packets will be set to the default value (NOCALL).

# DireCpp::init( std::string source , std::string destination )

## Return type:
`int`

## Description:
Used to connect to the server with the settings specified in the class constructor. If the connection was successfully stablished, the function will return a `0`, otherwise, it'll return `-1`. It's required to succesfully call this function (or it's alternative) before any further communications are done via a DireCpp object. The callsigns used for transmitting and receving packets will be set to `source` (for the transmitting) and `destination` (for receiving).

# DireCpp::change_addr( std::string source , std::string destination )

## Return type:
`None`

## Description:
Changes the DireCpp object's call signs by the ones specified by `source` (for the transmitting) and `destination` (for receiving).

# DireCpp::transmit( uint8_t * payload, uint32_t size )

## Return type:
`uint8_t`

## Description:
Used to send 8 bit data to the TNC. The pointer `payload` must contain the memory address of where the data to be sent is located, and `size` must contain the size of that data. If no errors were encountered, the amount of bytes sent is returned, otherwise a `-1` is returned.

# DireCpp::receive( void )

## Return type:
`AX25::aprs_packet`

## Description:
Used to receive an array of bytes from the TNC. The packet is returned in the shape of an APRS packet (`AX25::aprs_packet`).

# DireCpp::receive_by_call( void )

## Return type:
`AX25::aprs_packet`

## Description:
Used to receive an array of bytes from the TNC, but only if said array is contained within a packet with a destination address equal to the direcpp object's source address. The packet is returned in the shape of an APRS packet (`AX25::aprs_packet`).

# DireCpp::send_string( std::string msg_str )

## Return type:
`int`

## Description:
Used to send a string of characters (`std::string`) to the TNC. If no errors were encountered, the amount of bytes sent is returned, otherwise a `-1` is returned.

# DireCpp::get_info_str(AX25::aprs_packet packet)

## Return type:
`std::string`

## Description
Returns the the information segment contained within an APRS packet (AX25::aprs_packet) as a string of characters (std::string).   
