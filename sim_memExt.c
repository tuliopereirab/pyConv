#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_WIDTH 12

typedef struct _memory{
    char *data;
}memory;
memory *memExt = NULL;

int read_memory(char addr[]);
int add_memory(char data[], char addr[]);
int memory_init();

int bin_to_dec(char bin[]);

int memory_init(){
    int i;
    if((memExt = (memory*)malloc(sizeof(memory)*MEMORY_SIZE)) == NULL)
        return -99;
    for(i=0; i<MEMORY_SIZE; i++){
        memExt[i].data = (char*)malloc(sizeof(memory)*DATA_WIDTH);
        strcpy(memExt[i].data, "00000000");
    }
    return 0;
}

int add_memory(char data[], char addr[]){
    if(strlen(data) != DATA_WIDTH)
        return -2;          // dado com largura incorreta
    if(strlen(addr) != ADDR_WIDTH)
        return -3;          // endereço com largura incorreta
    if(bin_to_dec(addr) >= MEMORY_SIZE)
        return -6;          // endereço maior que o limite máximo
    strcpy(memExt[bin_to_dec(addr)].data, data);
    return 0;
}

int read_memory(char addr[]){
    if(bin_to_dec(addr) >= MEMORY_SIZE)
        return -1;
    else
        return bin_to_dec(memExt[bin_to_dec(addr)].data);
}
