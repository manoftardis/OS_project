#include "bitmap_allocator.h"

BitMapAllocatorResult BitMapAllocator_init(BitMapAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size){
    //controllo se abbiamo abbastanza memoria
    int requested_memory = num_items*(item_size+sizeof(int));
    if(memory_size < requested_memory)
        return NotEnoughMemory;

    allocator->item_size = item_size;
    allocator->size = num_items;
    allocator->buffer_size = item_size*num_items;
    allocator->size_max = num_items;

    allocator->buffer = memory_block; //utilizziamo la parte superiore per memoria
    // continuare
}

void* BitMapAllocator_getBlock(BitMapAllocator* allocator){
    
}
