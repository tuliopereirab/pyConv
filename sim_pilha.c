#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_WIDTH 12

int add_stack(char data[]);
int remove_stack();
int pilha_init();


int bin_to_dec(char bin[]);

typedef struct _Pilha{
    char *data;
}Pilha;

Pilha *pilha = NULL;
int tos=0;

int pilha_init(){
    int i;
    if((pilha = (Pilha*)malloc(sizeof(Pilha)*MEMORY_SIZE)) == NULL)
        return -1;
    for(i=0; i<MEMORY_SIZE; i++){
        pilha[i].data = (char*)malloc(sizeof(char)*DATA_WIDTH);
        strcpy(pilha[i].data, "00000000");
    }
    return 0;
}

int add_stack(char data[]){
    tos++;
    if(tos >= MEMORY_SIZE)
        return -1;
    strcpy(pilha[tos].data, data);
    return 0;
}
int remove_stack(){
    char data[DATA_WIDTH];
    strcpy(data, pilha[tos].data);
    tos--;
    if(tos < 0)
        return -1;
    else
        return bin_to_dec(data);    // retorna o valor decimal do dado binário
}
