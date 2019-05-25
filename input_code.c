#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096       // 12 bits

int gerencia_entrada(int posMemoria, char entrada[]);
void aguardar_entrada(int arqType);

// externas
void help_init();
void inicio_geradorMem(char nomeArq[]);
int inicio_conversor(int posMemoria, char comando[], char argumento[]);
int analise_argumento(char comando[], char argumento[], int line);
int check_variaveis(char comando[], char arg[]);
int verifica_variavel(char variavel[]);
void error_message(int id);
int check_argumento(char comando[]);
int check_comando(char comando[]);
int check_tos(char comando[]);
int check_popJump(char comando[]);
void inicio_geradorMem_mif(char nomeArq[], int higherLine);

void aguardar_entrada(int arqType){
    int statusQuit=0, valor_retorno, line=0, newLine, lineTemp, higherLine=0;
    char arqName[20];
    char entrada[100];
    char commandHelp[50];
    //arqName = (char*)malloc(sizeof(char)*20);
    printf("Inicializado, aguardando entradas: \n");
    while(statusQuit!=1){
        printf("%i-> ", line);
        gets(entrada);
        __fpurge(stdin);
        if(((strcmp(entrada, "quit")) == 0) || ((strcmp(entrada, "QUIT")) == 0) || ((strcmp(entrada, "Quit")) == 0)){
            statusQuit = 1;
            if(line>0){
                printf("Nome do arquivo: ");
                scanf("%s", &arqName);
                __fpurge(stdin);
                if(arqType == 1){            // gerador de arquivo .mif
                    inicio_geradorMem_mif(arqName, higherLine);
                    exit(EXIT_SUCCESS);
                }else if(arqType == 0){
                    inicio_geradorMem(arqName);
                    exit(EXIT_SUCCESS);
                }else{
                    inicio_geradorMem(arqName);
                    inicio_geradorMem_mif(arqName, higherLine);
                    exit(EXIT_SUCCESS);
                }
            }
        }else if(((strcmp(entrada, "line")) == 0) || ((strcmp(entrada, "LINE")) == 0) || ((strcmp(entrada, "Line")) == 0)){
            printf("Linha destino: ");
            scanf("%i", &lineTemp);
            __fpurge(stdin);
            if(lineTemp < MEMORY_SIZE)
                newLine = lineTemp;
            else
                printf("Valor superior ao número máximo de tamanho de memória (%i).\n", MEMORY_SIZE);
        }else if(((strcmp(entrada, "help")) == 0) || ((strcmp(entrada, "HELP")) == 0) || ((strcmp(entrada, "Help")) == 0)){
            printf("Comando: ");
            scanf("%s", &commandHelp);
            __fpurge(stdin);
            help_init(commandHelp);
            newLine = line;
        }else
            newLine = gerencia_entrada(line, entrada);      // retorna o valor da nova linha, que poderá ser incrementado por 2 ou 1, dependendo da instrução

            if((statusQuit != 1) && (newLine < 0))     // newLine<0 indica que houve um erro qualquer
                error_message(newLine);
            else{
                line = newLine;
                if(line > higherLine)
                    higherLine = newLine;
            }
    }
}

int gerencia_entrada(int pMemory, char entrada[]){
    int i, j, newLine, controleEspacos, tamEntrada = strlen(entrada), checkTos, analiseArg;
    char comando[20], argumento[20];
    controleEspacos = 0;
    j=0;
    for(i=0; i<tamEntrada; i++){
        if(controleEspacos == 0){
            if(entrada[i] == ' '){
                comando[j] = '\0';
                controleEspacos++;
                j=0;
            }else
                comando[j++] = entrada[i];
        }else if(controleEspacos == 1){
            if(entrada[i] == ' '){
                argumento[j] = '\0';
                controleEspacos++;
                j=0;
            }else
                argumento[j++] = entrada[i];
        }else
            return -1;
    }

    if(check_comando(comando) == 0)  // comando invalido
        return -4;

    if(controleEspacos == 0)
        if(check_argumento(comando) == 1)    // comando precisa de argumento
            return -3;

    if((analiseArg = analise_argumento(comando, argumento, pMemory)) < 0)
        return analiseArg;
    if(check_variaveis(comando, argumento) < 0)
        return -11;
    if(check_popJump(comando) < 0)
        return -12;
    if((checkTos = check_tos(comando)) < 0)
        return checkTos;
    return inicio_conversor(pMemory, comando, argumento);
}
