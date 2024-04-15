#define _DEFAULT_SOURCE

#include "buddy_allocator.h"
#include "mmap_allocator.h"
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

#define BUFFER_SIZE 10240
#define BUDDY_LEVELS 5
#define MEMORY_SIZE (1024*1024) //1MB
#define MIN_BUCKET_SIZE (MEMORY_SIZE >> (BUDDY_LEVELS))

uint8_t buffer[BUFFER_SIZE]; //10KB sono più che sufficenti per la gestione della bitmap
char memory[MEMORY_SIZE];

BuddyAllocator allocator;

void pseudo_init(void){
    BuddyAllocator_init(&allocator, BUDDY_LEVELS, buffer, BUFFER_SIZE, memory, MIN_BUCKET_SIZE);
}

void *pseudo_malloc(size_t size){
    void* ptr;
    if(size < (PAGE_SIZE/4)){
        ptr = BuddyAllocator_malloc(&allocator, size);
    }else{
        printf("Allochiamo tramite mmap\n");
        ptr = mmap_malloc(size);
    }
    return ptr;
}

void pseudo_free(void* mem){

    //estraiamo la size del blocco per decidere quale free eseguire
    int* ptr = (int*)mem;
    int size = ptr[-1];
    if(size < (PAGE_SIZE/4)){
        BuddyAllocator_free(&allocator, mem);
    }else{
        printf("Deallochiamo tramite munmap\n");
        mmap_free(mem);
    }

}
