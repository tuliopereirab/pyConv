#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096       // 12 bits

int check_entrada(int posMemoria, char entrada[]);
void aguardar_entrada();
void error_message(int id);

void inicio_conversor(int posMemoria, char comando[], char argumento[]);
// int main(){
//     aguardar_entrada();
// }

void aguardar_entrada(){
    int status=0, valor_retorno, linha=0, lineTemp;
    char* arqName;
    arqName = (char*)malloc(sizeof(char)*20);
    char entrada[100];
    printf("Inicializado, aguardando entradas: \n");
    while(status!=1){
        printf("%i-> ", linha);
        gets(entrada);
        __fpurge(stdin);
        if(((strcmp(entrada, "quit")) == 0) || ((strcmp(entrada, "Quit")) == 0) || ((strcmp(entrada, "QUIT")) == 0)){
            status = 1;
            printf("Nome do arquivo: ");
            gets(arqName);
            __fpurge(stdin);
            inicio_geradorMem(arqName);
        }if(((strcmp(entrada, "line")) == 0) || ((strcmp(entrada, "Line")) == 0) || ((strcmp(entrada, "LINE")) == 0)){
            printf("Linha: ");
            scanf("%i", &lineTemp);
            __fpurge(stdin);
            if(lineTemp < MEMORY_SIZE-1)
                linha = lineTemp;
            else
                printf("Valor superior ao tamanho ta memoria.\n");
        }else
            valor_retorno = check_entrada(linha, entrada);

        if((status != 1) && (valor_retorno != 0)) // ocorreu um erro e o comando não é quit
            error_message(valor_retorno);
        else
            linha++;
    }
    printf("Entrada finalizada.\n");
}

void error_message(int id){
    switch(id){
        case 10:     // erro de formatação
            printf("Utilize o formato: [comando] [valor_entrada (se necessário)]\n");
            printf("Exemplo: LOAD_CONST 15\n\n");
            break;
        case 11:     // posicao de memória invalido
            printf("O valor de 'num_linha' deve estar entre 0 e 255.\n");
            break;
        case 12:
            printf("O comando utilizado necessita de um argumento.\n"); // comando necessita argumento
            break;
        case 13:
            printf("Comando digitado é invalido.\n");
    }
}

int check_entrada(int posMemoria, char entrada[]){
    int i, j, controle, check_arg, check_comValido, tamEntrada = strlen(entrada);
    char posMem_char[5], comando[20], argumento[20];

    controle=1;
    j=0;
    for(i=0; i<tamEntrada; i++){
        if(controle == 1){
            if(entrada[i] == ' '){
                comando[j] = '\0';
                j=0;
                controle++;
            }
        else
            comando[j++] = entrada[i];

        }else if(controle == 2){    // salvar o argumento
            if(entrada[i] == ' '){
                argumento[j] = '\0';
                j=0;
                controle++;
            }else
                argumento[j++] = entrada[i];
        }else if(controle > 2)
            return 10;
    }
    if((controle == 0) || (controle > 2))
        return 10;

    if((check_comValido = check_comando(comando)) == 0) // comando invalido
        return 13;

    if(controle == 1)
        if((check_arg = check_argumento(comando)) == 1) // comando não precisa argumento
            return 12;

    inicio_conversor(posMemoria, comando, argumento);


}

int check_argumento(char comando[]){
    if((strcmp(comando, "BINARY_ADD")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "BINARY_SUBTRACT")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "BINARY_MULTIPLY")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "BINARY_DIVIDE")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "INPLACE_ADD")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else
        return 1;
}

int check_comando(char comando[]){
    if((strcmp(comando, "LOAD_CONST")) == 0)
        return 1;
    else if((strcmp(comando, "LOAD_FAST")) == 0)
        return 1;
    else if((strcmp(comando, "STORE_FAST")) == 0)
        return 1;
    // else if((strcmp(comando, "LOAD_GLOBAL")) == 0)
    //     return 1;
    else if((strcmp(comando, "BINARY_ADD")) == 0)
        return 1;
    else if((strcmp(comando, "BINARY_SUBTRACT")) == 0)
        return 1;
    else if((strcmp(comando, "BINARY_MULTIPLY")) == 0)
        return 1;
    else if((strcmp(comando, "BINARY_DIVIDE")) == 0)
        return 1;
    else if((strcmp(comando, "INPLACE_ADD")) == 0)
        return 1;
    else if((strcmp(comando, "POP_JUMP_IF_FALSE")) == 0)
        return 1;
    else if((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0)
        return 1;
    else if((strcmp(comando, "JUMP_FORWARD")) == 0)
        return 1;
    else if((strcmp(comando, "JUMP_ABSOLUTE")) == 0)
        return 1;
    else if((strcmp(comando, "COMPARE_0P")) == 0)
        return 1;
    // else if((strcmp(comando, "SETUP_LOOP")) == 0)
    //     return 1;
    else if((strcmp(comando, "CALL_FUNCTION")) == 0)
        return 1;
    else if((strcmp(comando, "RETURN_VALUE")) == 0)
        return 1;
    // else if((strcmp(comando, "POP_BLOCK")) == 0)
    //     return 1;
    else
        return 0;       // indica que o comando não existe

}
