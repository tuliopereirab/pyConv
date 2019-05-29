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
int adicionar_valor(char palavra[], int posicao, char cmd[], char arg[], int status);
void retornar_matriz();
// ------------------------------

// ------------------------------
// help.c
void help_inicializacao();
// ------------------------------

// simulator
int init_simulator();

int main(int argc, char **argv){
    int op, status;
    status = inicializa_matriz();       // criação da matriz zerada
    if(status == 1)
        status = init_simulator();
    else{
        printf("Erro ao inicializar a matriz.\n");
        exit(EXIT_FAILURE);
    }
    if(status < 0)
        exit(EXIT_FAILURE);

    if(argc == 1)
        op = 99;            // ambos
    else{
        if((strcmp(argv[1], "-mif")) == 0)
            op = 1;         // arq .mif
        if((strcmp(argv[1], "-mem")) == 0)
            op = 0;         // arq .mem
        else if(((strcmp(argv[1], "-h")) == 0) || ((strcmp(argv[1], "-help")) == 0)){
            help_inicializacao();
            return 0;
        }else{
            printf("Opção digitada é inválida.\nUtilize './Compilador -h' para mais informações.\n");
            return 0;
        }
    }

    aguardar_entrada(op);
    //inicio_geradorMem("segundoArq", algoritmo);
}
