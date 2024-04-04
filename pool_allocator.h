
typedef enum {
    Success = 0,
    NotEnoughMemory = -1,
    UnalignedFree = -2,
    OutOfRange = -3,
    DoubleFree = -4,
}   PoolAllocatorResult;

typedef struct PoolAllocator{

    char* buffer;       //buffer gestisto dal sistema
    int* free_list;   //list of linked objects
    int buffer_size;    //grandezza buffer

    int size;           //numero di blocchi liberi
    int size_max;       //numero massimo di blocchi
    int item_size;      //grandezza del singolo blocco

    int first_idx;      //puntatore al primo contenitore
    int bucket_size;    // grandezza del contenitore

} PoolAllocator;

//inizializza l'allocatore
PoolAllocatorResult PoolAllocator_init(PoolAllocator* allocator, int item_size, int num_items, char* memory_block, int memory_size);

void* PoolAllocator_getBlock(PoolAllocator* allocator);

PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void* block);

