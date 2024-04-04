#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "buddy_allocator.h"


//funzioni per la ricerca degli indici associati dato un generico indice

int levelIdx(size_t idx){
    return (int)floor(log2(idx));
}

int startIdx(int idx){
    return (idx-(1<<levelIdx(idx)));
}

int buddyIdx(int idx){
    if(idx&0x1){
        return idx-1;
    }
    return idx+1;
}

int parentIdx(int idx){
    return idx/2;
}

int BuddyAllocator_calcSize(int num_levels){
    int list_items = 1<<(num_levels+1); //massimo numero di allocazioni possibili
    int list_alloc_size = sizeof(int)*list_items; //grandezza del singolo elemento della lista
    return list_alloc_size;
}

void BuddyAllocator_init(BuddyAllocator* allocator, int num_levels,char* buffer, int buffer_size, char* memory, int min_bucket_size){
    allocator->num_levels = num_levels;
    allocator->memory = memory;
    allocator->min_bucket_size = min_bucket_size;

    assert(num_levels<MAX_LEVELS); //controlliamo che esistano meno livelli del numero massimo
    assert(buffer_size>= BuddyAllocator_calcSize(num_levels)); //controlliamo se esiste abbastanza spazio per immagazzinare le informazioni

    int list_items = 1<<(num_levels+1); //numero massimo di allocazioni
    int list_alloc_size = sizeof(int)*list_items;

    //informazioni relative al allocatore
    printf("levels: %d,  max entries: %d,  bucket size: %d,  memoria gestita: %d bytes\n",num_levels, list_alloc_size, min_bucket_size, (1<<num_levels)*min_bucket_size);

    char *list_start = buffer;
    BitMapAllocatorResult  init_result = BitMapAllocator


}
