#include <stdio.h>
#include "main.c"
//#include "hexToDec.c"
#include "gerenciador_matriz.c"
#include "conversor.c"
#include "controle_variaveis.c"
#include "input_code.c"
#include "checks.c"


#define MEMORY_SIZE 4096
#define MAX_CONJUNTOS 1024
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16


// ------------------------------
// gerador_mem.c
void inicio_geradorMem(char nomeArq[]);
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
// controle_variaveis.c
char *decimal_to_binary_addr(int n);
char *decimal_to_binary_code(int n);
char *busca_variavel(char chave[]);
int adicionar_variavel(char chave[]);
//------------------------------

// ------------------------------
// conversor.c
int inicio_conversor(int posMemoria, char comando[], char argumento[]);
char* montar_comando(char comando_bin[], char arg_bin[], int usaArg);
char *verCodigo_comando(char comando[]);
char* verComparacao(int val);
//------------------------------

// ------------------------------
// input_code.c
int gerencia_entrada(int pMemory, char entrada[]);
void aguardar_entrada();
// ------------------------------


// ------------------------------
// checks.c
void error_message(int id);
int check_argumento(char comando[]);
int check_comando(char comando[]);
// ------------------------------
