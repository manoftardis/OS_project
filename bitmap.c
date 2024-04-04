#include <assert.h>
#include "bitmap.h"

int BitMap_getBytes(int bits){
    return bits/8 + (bits%8)!= 0;
}

int BitMap_init(BitMap* bit_map, int num_bits, uint8_t* buffer){
    bit_map->buffer = buffer;
    bit_map->num_bits = num_bits;
    bit_map->buffer_size = BitMap_getBytes(num_bits);
}


void BitMap_setBit(BitMap *bit_map, int bit_num, int status){
    int byte_num = bit_num >> 3;
    assert(byte_num<bit_map->buffer_size);
    int bit_inside_byte = byte_num&0x03;
    if (status){
        bit_map->buffer[byte_num] |= (1<<bit_inside_byte);
    }else{
        bit_map->buffer[byte_num] &= ~(1<<bit_inside_byte);
    }
}

int BitMap_bit(const BitMap *bit_map, int bit_num){
    int byte_num = bit_num>>3;
    assert(byte_num<bit_map->buffer_size);
    int bit_inside_byte = byte_num&0x03;
    return (bit_map->buffer[byte_num] & (1<<bit_inside_byte))!= 0;
}
