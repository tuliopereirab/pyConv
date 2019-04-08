#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N_POSICOES_MEM 256

FILE *arq;

struct codigo{
    char posicao[16];
};

struct codigo **algoritmo;

int main(){
    inicio_geradorMem("primeiroArq");
}

int inicio_geradorMem(char nomeArq[]){    // deve também receber a matriz da struct
    int status;
    if((status = abrirArq(nomeArq)) == 0)
        return 0;
    status = escrita_arqMem();
    return status;
}

int abrirArq(char nomeArq[]){
    int tamNome = strlen(nomeArq);
    char *nomeCompleto;
    nomeCompleto = (char*)malloc(sizeof(char)*tamNome+4);
    strcpy(nomeCompleto, nomeArq);
    strcat(nomeCompleto, ".mem");
    if((arq = fopen(nomeCompleto, "w+")) != NULL)
        return 1;
    else
        return 0;
}

int escrita_arqMem(){ // converter pra hexadecimal       (deve também receber a matriz da struct)
    int i, j;
    j=99;
    for(i=(N_POSICOES_MEM-1); i>=0; i--){
        if(j==99){   // inicialização
            fprintf(arq, "// memory data file (do not edit the following line - required for mem load use)\n");
            fprintf(arq, "// instance=/teste/processor/comp_memInstr/memInstr\n");
            fprintf(arq, "// format=mti addressradix=h dataradix=s version=1.0 wordsperline=4\n");
            fprintf(arq, "%i: ", i);
            j=0;
        }else if(j==4){
            fprintf(arq, "\n%i: ", i);
            j=0;
        }else
            fprintf(arq, " ");
        fprintf(arq, "0000000000000000");
        j++;
    }
    fprintf(arq, "\n");
}
