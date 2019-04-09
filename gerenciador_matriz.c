#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_CONJUNTOS 64
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

struct codigo{
    char *palavra;
};

struct codigo **algoritmo;

int main(){
    int status = inicializa_matriz();
    printar_matriz();
}

int inicializa_matriz(){
    int i, j;
    algoritmo = (struct codigo**)malloc(sizeof(struct codigo*) * MAX_CONJUNTOS);
    for(i=0; i<MAX_CONJUNTOS; i++){
        algoritmo[i] = (struct codigo*)malloc(sizeof(struct codigo) * PALAVRAS_CONJUNTO);
        for(j=0; j<PALAVRAS_CONJUNTO; j++){
            algoritmo[i][j].palavra = (char*)malloc(sizeof(char)*LENGTH_PALAVRA);
            strcpy(algoritmo[i][j].palavra, "UUUUUUUUUUUUUUUU\0");
        }
    }
    return 1;
}

void printar_matriz(){
    int i, j;
    for(i=0; i<MAX_CONJUNTOS; i++){
        for(j=0; j<PALAVRAS_CONJUNTO; j++){
            printf("%s ", algoritmo[i][j].palavra);
        }
        printf("\n");
    }
}
