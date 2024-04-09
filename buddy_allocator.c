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

//funzione stampa bitmap per debugging
void BitMap_print(BitMap* bitmap){
    int to_print = 0;
    int level = -1;
    int total = levelIdx(bitmap->num_bits)-1;
    for(int i = 0; i < bitmap->num_bits; i++){
        if(to_print == 0){
            if(level == total){
                break;
            }
            printf("Livello %d \t", ++level);
            for(int j = 0; j < (1 << total)-(1 << level); j++){
                printf(" "); //stampiamo spazi per formattazione
            }
            to_print = 1 << level; // al livello successivo si devo stampare piu bit
        }
        printf("%d", BitMap_bit(bitmap, i));
        --to_print;
    }
    printf("\n");
}

//setta i bit dei genitori a status
void setStatus_parents(BitMap* bitmap, int bit_num, int status){
    BitMap_setBit(bitmap, bit_num, status);
    while(bit_num != 0){
        bit_num = parentIdx(bit_num);
        BitMap_setBit(bitmap, bit_num, status);
    }
}

//ricorsivamente setta i bit dei figli a status
void setStatus_children(BitMap* bitmap, int bit_num, int status){
    if(bit_num < bitmap->num_bits){
        BitMap_setBit(bitmap, bit_num, status);
        setStatus_children(bitmap, bit_num*2, status);
        setStatus_children(bitmap, bit_num*2+1, status);
    }

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

    //controlliamo se abbiamo abbastanza memoria per gestire le strutture interne
    assert (buffer_size>=BuddyAllocator_calcSize(num_levels));

    //informazioni relative al allocatore
    printf("levels: %d\n"
            "max entries: %d\n"
            "bucket size: %d\n"
            "memoria gestita: %d bytes\n",
            "memoria riservata alla bitmap: %d bytes",
            num_levels, list_alloc_size, min_bucket_size, (1<<num_levels)*min_bucket_size, buffer_size);

    //buffer per la lista si trova alla fine della bitmap
    printf("Allocazione della BitMap");
    BitMap_init(allocator->bitmap, num_bits, buffer);
    BitMap_print(allocator->bitmap);

    return 1;
}

void* BuddyAllocator_malloc(BuddyAllocator* allocator, int size){
    //controllo grandezza memoria allocazione
    if(size == 0){
        return NULL;
    }
    int mem_size = (1<<allocator->num_levels)*allocator->min_bucket_size;
    //calcoliamo il livello dove inserire il banco di memoria
    int level = floor(log2(mem_size/(size+8)));
    int start_size = allocator->min_bucket_size << (allocator->num_levels-level);

    if(level > allocator->num_levels)
        level = allocator->num_levels;

    // controlliamo se esiste una locazione che può ospitare l'allocazione
    int free_idx = -1;
    for(int i = firstIdx(level); i < firstidx(level+1); i++){
        if(!BitMap_bit(&allocator->bitmap,i)){ //controlliamo se il blocco è libero
            free_idx = i;
            break;
        }
    }
    //non è stato trovato un blocco libero a quel livello
    if(free_idx == -1){
        printf("Non è stato possibile trovare blocchi liberi. MEMORY FAULT \n");
        return NULL;
    }

    //procediamo a settare i bit che indicano che il blocco è stato assegnato
    setStatus_parents(allocator->bitmap, free_idx, 1);
    setStatus_children(allocator->bitmap, free_idx, 1);

    char* indirizzo = allocator->memory + startIdx(free_idx) * start_size;
    ((int*)indirizzo)[0] = free_idx; // indirizzo dell'indice da usare nella free;
    BitMap_print(allocator->bitmap);
    return (void*)(indirizzo+sizeof(int)); // spostiamo l'indirizzo effettivo di 1 int per evitare di sovrascrivere l'indice
}

//funzione che ricorsivamente setta la bitmap
void merge(BitMap* bitmap, int idx){
    //controllo se il bit su cui vogliamo eseguire il merge è gia libero
    assert("Bit gia libero" && !BitMap_bit(bitmap, idx));

    //controllo se siamo nella radice
    if(idx == 1)
        return;

    int idx_buddy = buddyIdx(idx);

    if(!BitMap_bit(bitmap,idx_buddy)){
        printf("Merge fra il blocco e il suo buddy\n");
        int parent_idx = parentIdx(idx);
        BitMap_setBit(bitmap, parent_idx, 0);
        merge(bitmap, parent_idx); // controlliamo anche se il parent può essere soggetto ad un merge
    }
}

void BuddyAllocator_free(BuddyAllocator* allocator, void *mem){
    if(mem == NULL){
        printf("Impossibile chiamare Free su memoria non allocata\n");
        return;
    }

    printf("Libero il blocco di memoria");

    int *ptr = (int*)mem;
    int idx_free = ptr[-1];

    int buddy_dim = allocator->min_bucket_size * (1 << (allocator->num_levels- levelIdx(idx_free)));
    char *ptr_to_free = allocator->memory + startIdx(idx_free) * buddy_dim;

    //controllo allinemanto e double free
    assert("Puntatore non allineato" && (int*)ptr_to_free == &ptr[-1]);
    assert("Double Free" && BitMap_bit(&allocator->bitmap, idx_free));

    //settiamo che tutti i figli sono liberi ed eseguiamo un merge
    setStatus_children(allocator->bitmap, idx_free, 0);
    merge(allocator->bitmap, idx_free);
    BitMap_print(allocator->bitmap);
}
