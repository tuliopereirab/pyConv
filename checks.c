#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N_POSICOES_MEM 4096
#define MAX_CONJUNTOS 1024
#define PALAVRAS_CONJUNTO 4
#define LENGTH_PALAVRA 16
#define DATA_WIDTH 8
#define DATA_MAX_NUM 255


int check_tos(char comando[]);
void error_message(int id);
int check_argumento(char comando[]);
int check_comando(char comando[]);
int analise_argumento(char comando[], char argumento[], int line);
int check_comparacao(char arg[]);
int check_variaveis(char comando[], char arg[]);
int check_popJump(char comando[]);

// externas
int verifica_variavel(char arg[]);

int tos_index=0, tos_func=0, cont_comp=0;

void error_message(int id){
    switch(id){
        case -1:     // erro de formatação
            printf("Utilize o formato: [comando] [valor_entrada (se necessário)]\n");
            printf("Exemplo: LOAD_CONST 15\n\n");
            break;
        case -2:     // posicao de memória invalido
            printf("O valor de 'num_linha' deve estar entre 0 e %i.\n", N_POSICOES_MEM-1);
            break;
        case -3:
            printf("O comando utilizado necessita de um argumento.\n"); // comando necessita argumento
            break;
        case -4:
            printf("Comando digitado é invalido.\n");
            break;
        case -5:
            printf("Instrução tornará o valor de topo da pilha inválido.\n");
            break;
        case -6:
            printf("Instrução tornará o valor de topo da pilha de funções inválido.\n");
            break;
        case -7:
            printf("O valor do argumento deve ser entre 0 e %i.\n", DATA_MAX_NUM);
            break;
        case -8:
            printf("O endereço de memória deve estar entre 0 e %i.\n", N_POSICOES_MEM-1);
            break;
        case -9:
            printf("A soma do valor com a linha atual da instrução deve estar entre 0 e %i.\n", N_POSICOES_MEM-1);
            break;
        case -10:
            printf("O valor de argumento para COMPARE_OP deve ser um dos pré-definidos. Utilize o comando 'help' para verificar.\n");
            break;
        case -11:
            printf("Variável acessada pelo 'LOAD_FAST' inexistente.\nUtilize 'LOAD_CONST' + 'STORE_FAST' para criá-la antes de acessá-la.\n");
            break;
        case -12:
            printf("Para realizar um 'POP_JUMP_IF_', é preciso que tenha sido feita uma comparação ('COMPARE_OP') anteriormente.\n");
    }
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
    else if((strcmp(comando, "BINARY_AND")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "BINARY_OR")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "BINARY_XOR")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "INPLACE_ADD")) == 0)
        return 0;  // indica que não tem erro, já que não precisa de argumento
    else if((strcmp(comando, "RETURN_VALUE")) == 0)
        return 0;   // indica que não tem erro, já que não precisa de argumento
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
    else if((strcmp(comando, "BINARY_AND")) == 0)
        return 1;
    else if((strcmp(comando, "BINARY_OR")) == 0)
        return 1;
    else if((strcmp(comando, "BINARY_XOR")) == 0)
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
    else if((strcmp(comando, "COMPARE_OP")) == 0)
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

int check_tos(char comando[]){                  // 0 -> está ok || -1 -> erro
    if((strcmp(comando, "LOAD_CONST")) == 0)
        if(tos_index < N_POSICOES_MEM){
            tos_index++;
            return 0;
        }else
            return -5;
    else if((strcmp(comando, "LOAD_FAST")) == 0)
        if(tos_index < N_POSICOES_MEM){
            tos_index++;
            return 0;
        }else
            return -5;
    else if((strcmp(comando, "STORE_FAST")) == 0)
        if(tos_index == 0)
            return -5;
        else{
            tos_index--;
            return 0;
        }
    else if((strcmp(comando, "BINARY_ADD")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }
    else if((strcmp(comando, "BINARY_SUBTRACT")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }
    else if((strcmp(comando, "BINARY_MULTIPLY")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }else if((strcmp(comando, "BINARY_DIVIDE")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }else if((strcmp(comando, "BINARY_AND")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }else if((strcmp(comando, "BINARY_OR")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }else if((strcmp(comando, "BINARY_XOR")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index--;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }
    // else if((strcmp(comando, "INPLACE_ADD")) == 0)      // não decrementa e pega apenas um valor para somar 1 a ele mesmo
    //     if(tos_index == 0)
    //         return -5;
    //     else
    //         return 0;
    else if((strcmp(comando, "COMPARE_OP")) == 0)
        if(tos_index <= 1)
            return -5;
        else{
            tos_index = tos_index-2;        // ele decrementa 2 e incrementa 1 (resultado)
            return 0;
        }
    else if((strcmp(comando, "CALL_FUNCTION")) == 0){
        tos_func++;
        return 0;
    }
    else if((strcmp(comando, "RETURN_VALUE")) == 0)
        if(tos_func == 0)
            return -6;
        else{
            tos_func--;
            return 0;
        }
    else
        return 0;       // indica que o comando não causa efeito em nenhuma pilha
}

int analise_argumento(char comando[], char argumento[], int line){
    int arg;
    if((strcmp(comando, "LOAD_CONST")) == 0)
        if((arg=atoi(argumento)) > DATA_MAX_NUM)
            return -7;
        else
            return 0;
    else if((strcmp(comando, "LOAD_FAST")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else if((strcmp(comando, "STORE_FAST")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else if((strcmp(comando, "POP_JUMP_IF_FALSE")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else if((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else if((strcmp(comando, "JUMP_FORWARD")) == 0)
        if((arg=atoi(argumento) + line) >= N_POSICOES_MEM)
            return -9;
        else
            return 0;
    else if((strcmp(comando, "JUMP_ABSOLUTE")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else if((strcmp(comando, "COMPARE_OP")) == 0)
        if((arg=atoi(argumento)) > DATA_MAX_NUM)
            return -7;
        else{
            if(check_comparacao(argumento) < 0)
                return -10;
            else
                return 0;
        }
    else if((strcmp(comando, "CALL_FUNCTION")) == 0)
        if((arg=atoi(argumento)) >= N_POSICOES_MEM)
            return -8;
        else
            return 0;
    else
        return 0;       // indica que o comando não existe
}

int check_comparacao(char arg[]){
    if((strcmp(arg, "0")) == 0)
        return 0;
    else if((strcmp(arg, "1")) == 0)
        return 0;
    else if((strcmp(arg, "2")) == 0)
        return 0;
    else
        return -10;             // erro
}

int check_variaveis(char comando[], char arg[]){
    if((strcmp(comando, "LOAD_FAST")) == 0)
        if(verifica_variavel(arg) == 0)
            return 0;
        else
            return -11;
    else
        return 0;
}

int check_popJump(char comando[]){
    if((strcmp(comando, "COMPARE_OP")) == 0){
        cont_comp++;
        return 0;
    }else if(((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0) || ((strcmp(comando, "POP_JUMP_IF_FALSE"))== 0)){
        if(cont_comp > 0){
            cont_comp--;
            return 0;
        }else
            return -12;
    }else
        return 0;
}
