#include "pool_allocator.h"
#include "bitmap.h"

#define MAX_LEVELS 16 //livello massimo di ricorsione

typedef struct{
    BitMap* bitmap;
    int num_levels;
    BitMapAllocator list_allocator;
    char* memory;
    int min_bucket_size;
} BuddyAllocator;


int BuddyAllocator_calcSize(int num_levels);

//inizializza
void BuddyAllocator_init(BuddyAllocator* allocator, int num_levels,char* buffer, int buffer_size, char* memory, int min_bucket_size);

//alloca della memoria
void* BuddyAllocator_malloc(BuddyAllocator* allocator, int size);

//libera tutta la memoria allocata
void BuddyAllocator_free(BuddyAllocator* allocator, void* mem);
