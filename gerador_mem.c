#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

FILE *arq;

struct codigo{
    char posicao[16];
}

struct codigo *algoritmo;

int entrada(char nomeArq[]){
    int status;
    if((status = abrirArq(nomeArq)) == 0)
        return 0;
    status = escrita_arqMem();
    return status;
}

int abrirArq(nomeArq[]){
    int tamNome = strlen(nomeArq);
    char *nomeCompleto;
    nomeCompleto = (char*)malloc(sizeof(char)*tamNome+4);
    strcpy(nomeCompleto, nomeArq);
    strcat(nomeCompleto, ".mem");
    if((arq = fopen(nomeArq, "w")) =! NULL)
        return 1;
    else
        return 0;
}

int escrita_arqMem(){ // converter pra hexadecimal

}
