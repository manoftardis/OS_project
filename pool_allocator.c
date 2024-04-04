#include "pool_allocator.h"

PoolAllocatorResult PoolAllocator_init(PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size){
    //controllo se abbiamo abbastanza memoria
    int requested_memory = num_items*(item_size+sizeof(int));
    if(memory_size < requested_memory)
        return NotEnoughMemory;

    allocator->item_size = item_size;
    allocator->size = num_items;
    allocator->buffer_size = item_size*num_items;
    allocator->size_max = num_items;

    allocator->buffer = memory_block; //utilizziamo la parte superiore per memoria
    allocator->free_list = (int*)(memory_block+item_size*num_items);

    for(int i=0; i<allocator->size-1; ++i){
        allocator->free_list[i] = i+1;
    }

    allocator->free_list[allocator->size-1] = -1; // settiamo l'ultimo elemento della lista
    allocator->first_idx = 0; //settiamo il primo elemento a 0 in modo da puntare alla lista
    return Success;
}

void* PoolAllocator_getBlock(PoolAllocator* allocator){
    if(allocator->first_idx == -1)
        return 0;

    //estrazione primo elemento dalla lista
    int detached_idx = allocator->first_idx;
    allocator->first_idx = allocator->free_list[allocator->first_idx];
    --allocator->size;

    allocator->free_list[detached_idx] = -2;

    //estraiamo il puntatore nel buffer
    char* block_address = allocator->buffer+(detached_idx*allocator->item_size);
    return block_address;
}

PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void* block_){

    char* block= (char*) block_;
    int offset = block - allocator->buffer;

    //se il blocco non è allieneato ritorniamo un errore
    if(offset% allocator -> item_size)
        return UnalignedFree;

    int idx = offset/allocator->item_size;

    //se siamo fuori dal buffer ritorniamo un errore
    if (idx < 0 || idx >= allocator->size_max)
        return OutOfRange;

    //controlliamo se il blocco è gia staccato
    if(allocator->free_list[idx] != -2)
        return DoubleFree;

    allocator->free_list[idx] = allocator->first_idx;
    allocator->first_idx = idx;
    ++allocator->size;
    return Success;
}
