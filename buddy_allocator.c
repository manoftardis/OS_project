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
    int list_alloc_size = (sizeof(BuddyItem)+sizeof(int))*list_items; //grandezza del singolo elemento della lista
    return list_alloc_size;
}

void BuddyAllocator_destroyItem(BuddyAllocator* alloc, BuddyItem* item){
    int level = item->level;
    //settiamo il valore nella bitmap a 0

}

void BuddyAllocator_init(BuddyAllocator* allocator, int num_levels, char* buffer, int buffer_size, char* memory, int min_bucket_size){

    assert(num_levels<MAX_LEVELS); //controlliamo che esistano meno livelli del numero massimo
    assert(buffer_size>= BuddyAllocator_calcSize(num_levels)); //controlliamo se esiste abbastanza spazio per immagazzinare le informazioni

    int list_items = 1<<(num_levels+1); //numero massimo di allocazioni
    int list_alloc_size = sizeof(int)*list_items;

    //numero di bit necessarri per l'allocazione della memoria
    int num_bits = list_items-1;

    allocator->num_levels = num_levels;
    allocator->memory = memory;
    allocator->min_bucket_size = min_bucket_size;

    //informazioni relative al allocatore
    printf("levels: %d\n"
            "max entries: %d\n"
            "bucket size: %d\n"
            "memoria gestita: %d bytes\n",
            "memoria riservata alla bitmap: %d bytes",
            num_levels, list_alloc_size, min_bucket_size, (1<<num_levels)*min_bucket_size, buffer_size);

    //buffer per la lista si trova alla fine della bitmap
    char *list_start = buffer;
    PoolAllocatorResult  init_result = PoolAllocator_init(&allocator->list_allocator, sizeof(BuddyItem), list_items, list_start, list_alloc_size);
    printf("Allocazione della BitMap");
    BitMap_init(allocator->bitmap, num_bits, buffer);
    return 1;
}

BuddyItem* BuddyAllocator_getBuddy(BuddyAllocator* allocator, int level){
    if(level < 0)
        return 0;
    assert(level <= allocator->num_levels);

    //controlliamo che ci siano spazi liberi a quel livello nella bitmap
}

void BuddyAllocator_releaseBuddy(BuddyAllocator* allocator, BuddyItem* item){
    //segnaliamo che il buddy è stato rilasciato
    int item_idx = item->idx;
    int n_byte = item_idx/8;
    int bit_pos = item_idx%8;
    allocator->bitmap->buffer[n_byte] &= ~(1<<bit_pos);

    //controlliamo se è il primo elemento della bitmap (capo della coda)
    if (parentIdx(item_idx) == 0)
        return;

    int buddy_idx = buddyIdx(item_idx);
      //forse controllare se l'indice è piu grande o piu piccolo e muovere bit_pos di 1 è più veloce
    int bit_pos = buddy_idx%8;
    //controlliamo se il suo buddy è assegnato, se cosi non facciamo nulla
    if((allocator->bitmap->buffer[n_byte] >> bit_pos) & (uint8_t)1)
        return;

    //liberare il livello

}
