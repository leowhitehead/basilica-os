#include <stddef.h>
#include <stdint.h>

#define RAND_MAX 32767
unsigned long next = 1;

int rand(){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % RAND_MAX+1; 
}

void srand(unsigned int seed){
    next = seed;
}

size_t strlen(const char* str){
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void delay(float t){   
    volatile int i,j;
    for(i=0;i<t;i++)
        for(j=0;j<250000;j++)
            __asm__("NOP");
}
 