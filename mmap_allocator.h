#include <stddef.h>

//alloca la memoria e restituisce un puntatore all'indirizzo
void *mmap_malloc(size_t size);

//dealloca la memoria
void mmap_free(void* mem);

