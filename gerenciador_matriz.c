#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define MAX_CONJUNTOS 1024
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

//---------------------------------------
int inicializa_matriz();
void printar_matriz();
int adicionar_valor(char palavra[], int posicao);
void retornar_matriz();
int abrirArq(char nomeArq[]);
int escrita_arqMem();
void inicio_geradorMem(char nomeArq[]);
//---------------------------------------

struct codigo{
    char *palavra;
    int status;
};

FILE *arq;
struct codigo **algoritmo;

 // int main(){
 //     int status = inicializa_matriz();
 //     adicionar_valor("0001101100011011", 15);
 //     adicionar_valor("0000111100001111", 255);
 //     adicionar_valor("1111111111111111", 0);
 //     inicio_geradorMem("terceiro");
 // }

int inicializa_matriz(){
    int i, j;
    algoritmo = (struct codigo**)malloc(sizeof(struct codigo*) * MAX_CONJUNTOS);
    for(i=0; i<MAX_CONJUNTOS; i++){
        algoritmo[i] = (struct codigo*)malloc(sizeof(struct codigo) * PALAVRAS_CONJUNTO);
        for(j=0; j<PALAVRAS_CONJUNTO; j++){
            algoritmo[i][j].palavra = (char*)malloc(sizeof(char)*LENGTH_PALAVRA);
            strcpy(algoritmo[i][j].palavra, "0000000000000000\0");   // inicializa a posição com um valor padrão de inicialização
            algoritmo[i][j].status = 0;   // indica que ainda não houve escrita na posição, evitando sobrescrever algo
        }
    }
    printf("Matriz inicializada com sucesso.\n");
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
    if(posicao > (MEMORY_SIZE-1)) return 11; // valor da posicao excede valor máximo esperado
    posI = posicao/4;
    posJ = posicao%4;
    if(algoritmo[posI][posJ].status == 1) return 0; // codigo indicando que já existe valor escrito na posição
    algoritmo[posI][posJ].status = 1;
    strcpy(algoritmo[posI][posJ].palavra, palavra);
    return 1;
}


// ------------------------------------------------------------------------------
//       ||||           ||||          ||||
//     ||    ||         ||  ||      ||    ||
//   ||||||||||||       |||||       ||    ||
// ||            ||     ||  ||        ||||||||
// ------------------------------------------------------------------------------

void inicio_geradorMem(char nomeArq[]){    // deve também receber a matriz da struct
    int status;
    if((status = abrirArq(nomeArq)) == 0)
        return 0;
    status = escrita_arqMem();
    fclose(arq);
    exit(EXIT_SUCCESS);
    //return status;
}

int abrirArq(char nomeArq[]){
    int tamNome = strlen(nomeArq);
    char *nomeCompleto;
    nomeCompleto = (char*)malloc(sizeof(char)*tamNome+4);
    strcpy(nomeCompleto, nomeArq);
    strcat(nomeCompleto, ".mem");
    if((arq = fopen(nomeCompleto, "w+")) != NULL)
        return 1;      // abriu o arquivo
    else
        return 0;      // erro ao abrir o arquivo
}

int escrita_arqMem(){ // converter pra hexadecimal       (deve também receber a matriz da struct)
    int i, j, z;
    fprintf(arq, "// memory data file (do not edit the following line - required for mem load use)\n"); // linha padrão
    fprintf(arq, "/// instance=/teste/processor/memInstr/memInstr\n");  // linha padrão
    fprintf(arq, "// format=mti addressradix=h dataradix=s version=1.0 wordsperline=4\n");  // linha padrão
    //fprintf(arq, "%x: ", i);

    //----------------------------------------
    //        ESCREVER MATRIZ NO ARQUIVO
    //----------------------------------------
    for(i=(MAX_CONJUNTOS-1); i>=0; i--){
        if(i*4+3 <= 16)
            fprintf(arq, "  ");     // deixa o espaçamento correto para 3 caracteres, sendo 2 vazios
        else if(i*4+3 <= 255)
            fprintf(arq, " ");      // deixa o espaçamento correto para 3 caracteres, sendo 1 vazio
        fprintf(arq, "%x: ", i*4+3); // %x faz um print diretamente em hexadecimal
        for(j=(PALAVRAS_CONJUNTO-1); j>=0; j--){
            fprintf(arq, "%s", algoritmo[i][j].palavra);
            if(j != 0) fprintf(arq, " ");
            z--;
        }
        fprintf(arq, "\n");
    }
    //----------------------------------------
    return 1;
}
