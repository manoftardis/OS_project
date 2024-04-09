#include "buddy_allocator.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 10
#define MEMORY_SIZE (1024*1024) //1MB
#define MIN_BUCKET_SIZE (MEMORY_SIZE >> (BUDDY_LEVELS))

char buffer[BUFFER_SIZE];
char memory[MEMORY_SIZE];

BuddyAllocator allocator;
int main(int argc, char** argv){

    //controlliamo se abbiamo abbastanza memoria per i buffer
    int req_size = BuddyAllocator_calcSize(BUDDY_LEVELS);
    printf('Size richiesta per l\'inizializzazione: %d/BUFFER_SIZE\n', req_size);

    printf("Iniziallizazione....\n");
    BuddyAllocator_init(&allocator, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SIZE);
    printf("Done... \n");

    void* p1=BuddyAllocator_malloc(&allocator, 100);
    void* p2=BuddyAllocator_malloc(&allocator, 100);
    void* p3=BuddyAllocator_malloc(&allocator, 100000);

    BuddyAllocator_free(&allocator, p1);
    BuddyAllocator_free(&allocator, p2);
    BuddyAllocator_free(&allocator, p3);


}
