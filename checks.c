#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void error_message(int id);
int check_argumento(char comando[]);
int check_comando(char comando[]);

void error_message(int id){
    switch(id){
        case -1:     // erro de formatação
            printf("Utilize o formato: [comando] [valor_entrada (se necessário)]\n");
            printf("Exemplo: LOAD_CONST 15\n\n");
            break;
        case -2:     // posicao de memória invalido
            printf("O valor de 'num_linha' deve estar entre 0 e 255.\n");
            break;
        case -3:
            printf("O comando utilizado necessita de um argumento.\n"); // comando necessita argumento
            break;
        case -4:
            printf("Comando digitado é invalido.\n");
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
