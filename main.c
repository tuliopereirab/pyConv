#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N_POSICOES_MEM 4096
#define MAX_CONJUNTOS 1024
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

// ------------------------------
// entrada_codigoAss.c
void aguardar_entrada(int arqType);
// ------------------------------

// ------------------------------
// gerador_mem.c
//int inicio_geradorMem(struct codigo *algo[][4], char nomeArq[]);
int abrirArq(char nomeArq[]);
int escrita_arqMem();
// ------------------------------

// ------------------------------
// gerenciador_matriz.c
int inicializa_matriz();
void printar_matriz();
int adicionar_valor(char palavra[], int posicao);
void retornar_matriz();
// ------------------------------

// ------------------------------
// help.c
void help_inicializacao();
// ------------------------------


int main(int argc, char **argv){
    int op;
    inicializa_matriz();       // criação da matriz zerada
    if((strcmp(argv[1], "-mif")) == 0)
        op = 1;         // arq .mif
    else if(((strcmp(argv[1], "-h")) == 0) || ((strcmp(argv[1], "-help")) == 0)){
        help_inicializacao();
        return 0;
    }else
        op = 0;         // arq .mem
    aguardar_entrada(op);
    //inicio_geradorMem("segundoArq", algoritmo);
}
