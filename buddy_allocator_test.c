#include "buddy_allocator.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10240
#define BUDDY_LEVELS 5
#define MEMORY_SIZE (1024*1024) //1MB
#define MIN_BUCKET_SIZE (MEMORY_SIZE >> (BUDDY_LEVELS))

uint8_t buffer[BUFFER_SIZE]; //10KB sono più che sufficenti per la gestione della bitmap
char memory[MEMORY_SIZE];

BuddyAllocator allocator;
int main(int argc, char** argv){

    //controlliamo se abbiamo abbastanza memoria per i buffer
    int req_size = BitMap_getBytes((1<<(BUDDY_LEVELS+1))-1);
    printf("Size richiesta per l'inizializzazione: %d/%d\n", req_size,BUFFER_SIZE);

    printf("Iniziallizazione....\n");
    BuddyAllocator_init(&allocator, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SIZE);
    printf("Done... \n");

    void* p1=BuddyAllocator_malloc(&allocator, 100);
    void* p2=BuddyAllocator_malloc(&allocator, 100);
    void* p3=BuddyAllocator_malloc(&allocator, 100000);
    void* p4=BuddyAllocator_malloc(&allocator, 100);
    void* p5=BuddyAllocator_malloc(&allocator, 100);


    BuddyAllocator_free(&allocator, p1);
    BuddyAllocator_free(&allocator, p2);
    BuddyAllocator_free(&allocator, p3);
    BuddyAllocator_free(&allocator, p4);
    BuddyAllocator_free(&allocator, p5);

}
