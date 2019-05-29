#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_WIDTH 12

int add_stack(char data[]);
int read_stack();
int pilha_init();
void changeTos(int newTos);
int verTos();
int check_number(char arg[]);


int bin_to_dec(char bin[]);

typedef struct _Pilha{
    char *data;
}Pilha;

Pilha *pilha = NULL;
int tos=0;

int pilha_init(){
    int i;
    if((pilha = (Pilha*)malloc(sizeof(Pilha)*MEMORY_SIZE)) == NULL)
        return -98;
    for(i=0; i<MEMORY_SIZE; i++){
        pilha[i].data = (char*)malloc(sizeof(char)*DATA_WIDTH);
        strcpy(pilha[i].data, "00000000");
    }
    return 0;
}

int add_stack(char data[]){
    if(strlen(data) != DATA_WIDTH)
        return -2;          // dado com largura incorreta
    if((tos+1) >= MEMORY_SIZE)
        return -5;          // topo atualizado terá valor acima do máximo
    tos++;
    strcpy(pilha[tos].data, data);
    return 0;
}
int read_stack(){
    char data[DATA_WIDTH];
    if((tos-1) < 0)
        return -4;
    strcpy(data, pilha[tos].data);
    tos--;
    return bin_to_dec(data);    // retorna o valor decimal do dado binário
}

int verTos(){
    return tos;
}

void changeTos(int newTos){
    tos = newTos;
}
