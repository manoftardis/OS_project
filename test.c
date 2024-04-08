#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void printBytes(uint8_t* bytesArray){
    for(int i = 0; i < 10; i++){
        printf("%02x ",bytesArray[i]);
    }
    printf("\n");
}

int main(){

    uint8_t* buffer = (uint8_t*) calloc(10,sizeof(uint8_t));
    printBytes(buffer);
    buffer[5] |= 1<<7;
    printBytes(buffer);
    buffer[5] &= ~(1<<7);
    printBytes(buffer);
    return 0;
}

