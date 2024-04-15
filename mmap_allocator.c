#define _DEFAULT_SOURCE

#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void *mmap_malloc(size_t size){
    size = size + sizeof(int); //spazie per l'header
    void* ptr = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    ((int*)ptr)[0] = size;
    return (void*)(ptr+sizeof(int));
}

void mmap_free(void* mem){

    int* ptr = (int*)mem;
    int size = ptr[-1];

    //unmappiamo la ma memoria e controlliamo se è stato eseguito tutto correttamente
    int ret = munmap(&ptr[-1], size);
    if(ret == -1){
        printf("Errore nella chiusura della memoria: %s \n", strerror(errno));
        return;
    }

    printf("Memoria deallocata senza problemi\n");

}
