#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _mem{
    char chave_acesso[20];  // nome da variável
};

typedef struct _mem mem;

char *decimal_to_binary(int n);
char *busca_variavel(char chave[]);

mem *memoria;
int tamMemoria = 0;          // a posição no vetor 'memoria' também é o endereço de memoria da memória física
                            // a struct serve para salvar a chave para cada posição
int main(){
    char *end;
    end = busca_variavel("hue1");
    end = busca_variavel("asd");
    printf("Endereco para asd: %s\n", end);
    end = busca_variavel("as");
    end = busca_variavel("asd");

    printf("-------------------\n\n");
    int i;
    for(i=0; i<tamMemoria; i++){
        printf("Chave: %s\tEndereco: %s\n", memoria[i].chave_acesso, busca_variavel(memoria[i].chave_acesso));
    }
}

int adicionar_variavel(char chave[]){
    char *endereco;
    if(tamMemoria == 0){
        tamMemoria++;
        memoria = (mem*)malloc(sizeof(mem)*tamMemoria);
    }else{
        tamMemoria++;
        memoria = (mem*)realloc(memoria, tamMemoria);
    }

    strcpy(memoria[tamMemoria-1].chave_acesso, chave);
    return tamMemoria-1;
}

char *busca_variavel(char chave[]){      // verifica se a chave de acesso (nome da variável) já
    int i, idVar;
    char *endereco;                              // redireciona para um endereço da memória física
    for(i=0; i<tamMemoria; i++){         // caso não, a chave é adicionada e ligada à um endereço
        if((strcmp(memoria[i].chave_acesso, chave)) == 0){
            endereco = decimal_to_binary(i);
            return endereco;
        }
    }
    idVar = adicionar_variavel(chave);
    endereco = decimal_to_binary(idVar);
    return endereco;
}


char *decimal_to_binary(int n)       // copiado de https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(8+1);

   for (c = 7 ; c >= 0 ; c--){
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
