#include <stddef.h>

//funzione che alloca la memoria e restituisce un puntatotre ad essa
void *pseudo_malloc(size_t size);

//funzione che si occupa di de allocare la memoria
void pseudo_free(void* ptr);

//wrapper per la funzione che inizializza l'allocatore del buddy allocator
void pseudo_init();
