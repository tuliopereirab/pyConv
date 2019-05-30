#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define MAX_CONJUNTOS 1024
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16

//---------------------------------------
int calcLine(int i, int j);
void arqTxt(char nomeArq[]);
int inicializa_matriz();
void printar_matriz();
int adicionar_valor(char palavra[], int posicao, char cmd[], char arg[], int status);
void retornar_matriz();
int abrirArq(char nomeArq[]);
int escrita_arqMem();
void inicio_geradorMem(char nomeArq[]);
int abrirArq_mif(char nomeArq[]);
int escrita_arqMem_mif(int higherLine);
void inicio_geradorMem_mif(char nomeArq[], int higherLine);
//---------------------------------------

struct codigo{
    char *palavra;
    int status;
    char *comandoASC;
    char *arg;
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
            algoritmo[i][j].comandoASC = (char*)malloc(sizeof(char)*LENGTH_PALAVRA);
            algoritmo[i][j].arg = (char*)malloc(sizeof(char)*LENGTH_PALAVRA);
            strcpy(algoritmo[i][j].palavra, "0000000000000000\0");   // inicializa a posição com um valor padrão de inicialização
            algoritmo[i][j].status = -1;   // indica que ainda não houve escrita na posição, evitando sobrescrever algo
            strcpy(algoritmo[i][j].comandoASC, "NOOP");
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

int adicionar_valor(char palavra[], int posicao, char cmd[], char arg[], int status){    // status: 0- palavra com argumento; 1- somente argumento (salvar em uma só palavra, não atribuir status); 2- sem argumento
    int tamPalavra = strlen(palavra);
    int posI, posJ;
    if(tamPalavra > 16) return 10; // codigo de erro indicando que a palavra excede o tamanho máximo
    if(posicao > (MEMORY_SIZE-1)) return 11; // valor da posicao excede valor máximo esperado
    posI = posicao/4;
    posJ = posicao%4;
    if(algoritmo[posI][posJ].status == 1) return 0; // codigo indicando que já existe valor escrito na posição
    algoritmo[posI][posJ].status = status;
    strcpy(algoritmo[posI][posJ].palavra, palavra);
    if(status == 0)     // salvar comando com argumento
        strcpy(algoritmo[posI][posJ].arg, arg);
    if((status == 0) || (status == 2))
        strcpy(algoritmo[posI][posJ].comandoASC, cmd);

    return 1;
}

int check_simulador(){
    int status, i, j, maxI, maxJ=PALAVRAS_CONJUNTO;
    maxI = MEMORY_SIZE/PALAVRAS_CONJUNTO;
    for(i=0; i<maxI; i++){
        for(j=0; j<maxJ; j++){
            if(status < 0)
                return status;
            if(algoritmo[i][j].status == 0)
                status = simulator(algoritmo[i][j].comandoASC, algoritmo[i][j].arg); // comando + argumento
            else if(algoritmo[i][j].status == 2)
                status = simulator(algoritmo[i][j].comandoASC, ""); // comando sem argumento
        }
    }
    return status;
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
        system("EXIT_FAILURE");
    status = escrita_arqMem();
    fclose(arq);
    arqTxt(nomeArq);
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

// ====================================================================================================================
// arquivo MIF
void inicio_geradorMem_mif(char nomeArq[], int higherLine){
    int status;
    if((status = abrirArq_mif(nomeArq)) == 0)
        system("EXIT_FAILURE");
    status = escrita_arqMem_mif(higherLine);
    fclose(arq);
    arqTxt(nomeArq);
    //return status;
}

int abrirArq_mif(char nomeArq[]){
    int tamNome = strlen(nomeArq);
    char *nomeCompleto;
    nomeCompleto = (char*)malloc(sizeof(char)*tamNome+4);
    strcpy(nomeCompleto, nomeArq);
    strcat(nomeCompleto, ".mif");
    if((arq = fopen(nomeCompleto, "w+")) != NULL)
        return 1;      // abriu o arquivo
    else
        return 0;      // erro ao abrir o arquivo
}

int escrita_arqMem_mif(int higherLine){ // converter pra hexadecimal       (deve também receber a matriz da struct)
    int i, j, z, lastI, lastJ, line=0;
    fprintf(arq, "-- Copyright (C) 1991-2013 Altera Corporation\n");
    fprintf(arq, "-- Your use of Altera Corporation's design tools, logic functions\n");
    fprintf(arq, "-- and other software and tools, and its AMPP partner logic \n");
    fprintf(arq, "-- functions, and any output files from any of the foregoing \n");
    fprintf(arq, "-- (including device programming or simulation files), and any \n");
    fprintf(arq, "-- associated documentation or information are expressly subject \n");
    fprintf(arq, "-- to the terms and conditions of the Altera Program License \n");
    fprintf(arq, "-- Subscription Agreement, Altera MegaCore Function License \n");
    fprintf(arq, "-- Agreement, or other applicable license agreement, including, \n");
    fprintf(arq, "-- without limitation, that your use is for the sole purpose of \n");
    fprintf(arq, "-- programming logic devices manufactured by Altera and sold by \n");
    fprintf(arq, "-- Altera or its authorized distributors.  Please refer to the \n");
    fprintf(arq, "-- applicable agreement for further details.\n\n");

    fprintf(arq, "-- Quartus II generated Memory Initialization File (.mif)\n\n");

    fprintf(arq, "WIDTH=%i;\n", LENGTH_PALAVRA);
    fprintf(arq, "DEPTH=%i;\n\n", MEMORY_SIZE);
    fprintf(arq, "ADDRESS_RADIX=UNS;\n");
    fprintf(arq, "DATA_RADIX=BIN;\n\n");

    fprintf(arq, "CONTENT BEGIN\n");

    lastI = higherLine/4;
    lastJ = higherLine%4;

    //printf("LastI: %i\nlastJ: %i\n", lastI, lastJ);

    //----------------------------------------
    //        ESCREVER MATRIZ NO ARQUIVO
    //----------------------------------------
    for(i=0; i<=lastI; i++){
        for(j=0; j<4; j++){
            if((j==lastJ) && (i==lastI)){
                fprintf(arq, "\t[%i..%i]\t:\t0000000000000000;\n", higherLine, MEMORY_SIZE-1);
                j=4+1;
            }else
                fprintf(arq, "\t%i\t:\t%s;\n", line, algoritmo[i][j].palavra);
            line++;
        }
    }
    fprintf(arq, "END;\n");
    //----------------------------------------
    return 1;
}
// ================================================================================
// ARQUIVO TXT
// ================================================================================


int calcLine(int i, int j){
    return i*PALAVRAS_CONJUNTO+j;
}

void arqTxt(char nomeArq[]){
    FILE *arqTxt;
    int i, j, maxI, maxJ=PALAVRAS_CONJUNTO;
    maxI = MEMORY_SIZE/PALAVRAS_CONJUNTO;
    if((arqTxt = fopen(nomeArq, "w+")) == NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<maxI; i++){
        for(j=0; j<maxJ; j++){
            if((algoritmo[i][j].status >= 0) && (algoritmo[i][j].status != 1)){
                if((algoritmo[i][j].status == 0) || (algoritmo[i][j].status == 2))
                    fprintf(arqTxt, "%i: %s ", calcLine(i, j), algoritmo[i][j].comandoASC);
                if(algoritmo[i][j].status == 0)
                    fprintf(arqTxt, "%s\n", algoritmo[i][j].arg);
                else
                    fprintf(arqTxt, "\n");
            }
        }
    }
    fclose(arqTxt);
    exit(EXIT_SUCCESS);
}
