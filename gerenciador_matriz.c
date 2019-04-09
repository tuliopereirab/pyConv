#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_CONJUNTOS 64
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

struct codigo{
    char *palavra;
    int status;
};

struct codigo **algoritmo;

int main(){
    int status = inicializa_matriz();
    adicionar_valor("0001101100011011", 15);
    adicionar_valor("0000111100001111", 255);
    printar_matriz();
}

int inicializa_matriz(){
    int i, j;
    algoritmo = (struct codigo**)malloc(sizeof(struct codigo*) * MAX_CONJUNTOS);
    for(i=0; i<MAX_CONJUNTOS; i++){
        algoritmo[i] = (struct codigo*)malloc(sizeof(struct codigo) * PALAVRAS_CONJUNTO);
        for(j=0; j<PALAVRAS_CONJUNTO; j++){
            algoritmo[i][j].palavra = (char*)malloc(sizeof(char)*LENGTH_PALAVRA);
            strcpy(algoritmo[i][j].palavra, "UUUUUUUUUUUUUUUU\0");   // inicializa a posição com um valor padrão de inicialização
            algoritmo[i][j].status = 0;   // indica que ainda não houve escrita na posição, evitando sobrescrever algo
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

int adicionar_valor(char palavra[], int posicao){
    int tamPalavra = strlen(palavra);
    int posI, posJ;
    if(tamPalavra > 16) return 10; // codigo de erro indicando que a palavra excede o tamanho máximo
    if(posicao > 255) return 11; // valor da posicao excede valor máximo esperado
    posI = posicao/4;
    posJ = posicao%4;
    if(algoritmo[posI][posJ].status == 1) return 0; // codigo indicando que já existe valor escrito na posição
    algoritmo[posI][posJ].status = 1;
    strcpy(algoritmo[posI][posJ].palavra, palavra);
}
