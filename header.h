#include <stdio.h>
#include "main.c"
//#include "hexToDec.c"
#include "gerenciador_matriz.c"
#include "gerador_mem.c"

#define N_POSICOES_MEM 256
#define MAX_CONJUNTOS 64
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16


// ------------------------------
// gerador_mem.c
int inicio_geradorMem(struct codigo *algo, char nomeArq[]);
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
