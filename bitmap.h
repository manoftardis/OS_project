//bit array

#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    int buffer_size;
    int num_bits;
}   BitMap;


//restituisce il numero di bits per tenere i booleani
int Bitmap_getBytes(int bits);

//inizializza la nostra bitmap su un array esterno
int BitMap_init(BitMap* bit_map, int num_bits, uint8_t *buffer);

//setta il numero di bit bit_num nella bitmap (0 o 1)
void BitMap_setBit(BitMap* bit_map, int bit_num, int status);

//inspeziona lo stato del bit bit_num
int BitMap_bit(const BitMap* bit_map, int bit_num);
