#include "pseudo_malloc.h"
#include <stdio.h>
#include <unistd.h>

int main(void){
    //inizialliziamo l'allocatore
    pseudo_init();

    /**
     * eseguiamo alcune allocazioni di varie grandezze per testare
     *
     *  p1,p2,p3 usano buddy allocator
     *  mentre p4,p5 usano mmap
     *
    */

    size_t page_size = sysconf(_SC_PAGESIZE);

    void* p1= pseudo_malloc(8);
    void* p2= pseudo_malloc(24);
    void* p3= pseudo_malloc(256);
    void* p6= pseudo_malloc((page_size/4)-1);

    void* p4= pseudo_malloc(page_size);
    void* p5= pseudo_malloc(page_size/2);
    void* p7= pseudo_malloc(page_size/4);

    // deallochiamo la memoria

    pseudo_free(p1);
    pseudo_free(p2);
    pseudo_free(p3);
    pseudo_free(p6);

    pseudo_free(p4);
    pseudo_free(p5);
    pseudo_free(p7);

    return 1;
}
