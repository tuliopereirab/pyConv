#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N_POSICOES_MEM 256
#define MAX_CONJUNTOS 64
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

// ------------------------------
// entrada_codigoAss.c
void aguardar_entrada();
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



int main(int argc, char **argv){
    inicializa_matriz();       // criação da matriz zerada
    aguardar_entrada();
    //inicio_geradorMem("segundoArq", algoritmo);
}
