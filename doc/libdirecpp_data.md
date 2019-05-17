# libdirecpp (DireCpp) data structures

## AX25::aprs_packet

```
struct aprs_packet{
    uint8_t call_orig[ MAX_ADDR_SIZE ]; //Call sign tx
    uint8_t call_dest[ MAX_ADDR_SIZE ]; //Call sign rx
    uint8_t digi[ MAX_ADDR_SIZE * MAX_RPTR ]; //Digipieater addresses
    uint8_t digi_count; //Digipiater count
    uint8_t info[MAX_INFO]; //Information segment of the packet
    uint32_t info_size; //Size of the information segment
    int size; //Size of the overall packet
};
```