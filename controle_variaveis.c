#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDR_LENGTH 16
#define CODE_LENGTH 8

struct _mem{
    char chave_acesso[20];  // nome da variável
};

typedef struct _mem mem;

char *decimal_to_binary_addr(int n);
char *decimal_to_binary_code(int n);
char *busca_variavel(char chave[]);
int adicionar_variavel(char chave[]);

mem *memoria;
int tamMemoria = 0;          // a posição no vetor 'memoria' também é o endereço de memoria da memória física
                            // a struct serve para salvar a chave para cada posição

int adicionar_variavel(char chave[]){
    char *endereco;
    if(tamMemoria == 0){
        tamMemoria++;
        memoria = (mem*)malloc(sizeof(mem)*tamMemoria);
    }else{
        tamMemoria++;
        memoria = (mem*)realloc(memoria, sizeof(mem)*tamMemoria);
    }

    strcpy(memoria[tamMemoria-1].chave_acesso, chave);
    return tamMemoria-1;
}

char *busca_variavel(char chave[]){      // verifica se a chave de acesso (nome da variável) já
    int i, idVar;
    char *endereco;                              // redireciona para um endereço da memória física
    for(i=0; i<tamMemoria; i++){         // caso não, a chave é adicionada e ligada à um endereço
        if((strcmp(memoria[i].chave_acesso, chave)) == 0){
            endereco = decimal_to_binary_addr(i);
            return endereco;
        }
    }
    idVar = adicionar_variavel(chave);
    endereco = decimal_to_binary_addr(idVar);
    return endereco;
}

char *decimal_to_binary_code(int n)       // copiado de https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(CODE_LENGTH+1);

   for (c = CODE_LENGTH-1; c >= 0 ; c--){
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';
   return pointer;
}

char *decimal_to_binary_addr(int n)       // copiado de https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(ADDR_LENGTH+1);

   for (c = ADDR_LENGTH-1; c >= 0 ; c--){
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';
   return pointer;
}
