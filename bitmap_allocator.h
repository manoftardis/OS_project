#include "bitmap.h"

typedef enum {
    Success = 0,
    NotEnoughMemory = -1,
    UnalignedFree = -2,
    OutOfRange = -3,
    DoubleFree = -4,
}   BitMapAllocatorResult;

typedef struct BitMapAllocator{

    char* buffer;       //buffer gestisto dal sistema
    //int* free_list    //list of linked objects
    int buffer_size;    //grandezza buffer

    int size;           //numero di blocchi liberi
    int size_max;       //numero massimo di blocchi
    int item_size;      //grandezza del singolo blocco

    //int first_idx;      //puntatore al primo contenitore
    //int bucket_size;    // grandezza del contenitore

} BitMapAllocator;

//inizializza l'allocatore
BitMapAllocatorResult BitMapAllocator_init(BitMapAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size);

void* BitMapAllocator_getBlock(BitMapAllocator* allocator);

BitMapAllocatorResult BitMapAllocator_releaseBlock(BitMapAllocator* allocator, void* block);

