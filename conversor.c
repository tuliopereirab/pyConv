#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inicio_conversor(int posMemoria, char comando[], char argumento[]);
char* montar_comando(char comando_bin[], char arg_bin[], int usaArg);
char *verCodigo_comando(char comando[]);
char* verComparacao(int val);


char *decimal_to_binary_addr(int n);
char *decimal_to_binary_code(int n);
char *busca_variavel(char chave[]);

int adicionar_valor(char palavra[], int posicao);
// int main(){
//     inicio_conversor(15, "LOAD_CONST", "15");
//     inicio_conversor(15, "BINARY_ADD", "");
//     inicio_conversor(15, "STORE_FAST", "hue");
//     inicio_conversor(15, "STORE_FAST", "papa");
// }

int inicio_conversor(int posMemoria, char comando[], char argumento[]){
    int status;
    char *codigoComando = verCodigo_comando(comando);
    char *arg_binary;
    char* comandoCompleto;     // string que será salva no arquivo .mem
    if((strcmp(comando, "LOAD_CONST")) == 0){
        arg_binary = decimal_to_binary_code(atoi(argumento));   // converte o valor decimal pra binario
        printf("Argumento binario: %s\n");
        comandoCompleto = montar_comando(codigoComando, arg_binary, 1);
    }else if((strcmp(comando, "LOAD_FAST")) == 0){
        arg_binary = busca_variavel(argumento);   // encontra o endereço pra variável "argumento"
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);   // gera um comando sem argumento
        //printf("Comando recebido: %s\nCodigo comando: %s\nComando completo: %s\nArgumento: %s\n", comando, codigoComando, comandoCompleto, arg_binary);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "STORE_FAST")) == 0){
        arg_binary = busca_variavel(argumento);   // encontra o endereço pra variável "argumento"
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "COMPARE_OP")) == 0){
        arg_binary = verComparacao(atoi(argumento));   // encontra o endereço pra variável "argumento"
        comandoCompleto = montar_comando(codigoComando, arg_binary, 1);
    }else if((strcmp(comando, "POP_JUMP_IF_FALSE")) == 0){
        arg_binary = decimal_to_binary_addr(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0){
        arg_binary = decimal_to_binary_addr(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "JUMP_ABSOLUTE")) == 0){
        arg_binary = decimal_to_binary_addr(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "JUMP_FORWARD")) == 0){
        arg_binary = decimal_to_binary_addr(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "BINARY_ADD")) == 0){
        arg_binary = NULL;   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }else if((strcmp(comando, "BINARY_SUBTRACT")) == 0){
        arg_binary = NULL;   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }else if((strcmp(comando, "BINARY_MULTIPLY")) == 0){
        arg_binary = NULL;   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }else if((strcmp(comando, "BINARY_DIVIDE")) == 0){
        arg_binary = NULL;   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }else if((strcmp(comando, "INPLACE_ADD")) == 0){
        arg_binary = NULL;   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }else if((strcmp(comando, "CALL_FUNCTION")) == 0){
        arg_binary = decimal_to_binary_addr(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
        status = adicionar_valor(comandoCompleto, posMemoria);
        posMemoria++;     // passa a apontar para a próxima posição (a do endereço)
        comandoCompleto = montar_comando(codigoComando, arg_binary, 2); // gera uma posição de memória interamente com o argumento
        status = adicionar_valor(comandoCompleto, posMemoria);
    }else if((strcmp(comando, "RETURN_VALUE")) == 0){
        arg_binary = NULL; //decimal_to_binary(atoi(argumento));   // converte o valor decimal pra binario
        comandoCompleto = montar_comando(codigoComando, arg_binary, 0);
    }

    posMemoria++;
    return posMemoria;
}

char* montar_comando(char comando_bin[], char arg_bin[], int usaArg){       // usaArg indica se o valor do argumento é utilizado ou não
    char *comandoCompleto;                                               // 1- sim; 0- não
    comandoCompleto = (char*)malloc(sizeof(char)*16);
    if(usaArg == 0){
        strcpy(comandoCompleto, "00000000");
        strcat(comandoCompleto, comando_bin);
    }else if(usaArg == 2){           // entrada de uma posição de endereço (os 16 bits serão o endereço)
        strcpy(comandoCompleto, arg_bin);
    }else{
        strcpy(comandoCompleto, arg_bin);
        strcat(comandoCompleto, comando_bin);
    }
    return comandoCompleto;
}

char *verCodigo_comando(char comando[]){
    char *load_const, *load_fast, *store_fast, *load_global;
    char *binary_add, *binary_subtract, *binary_multiply, *binary_divide, *inplace_add;
    char *pop_jump_if_false, *pop_jump_if_true, *jump_forward, *jump_absolute;
    char *compare_op, *call_function, *return_value;

    load_const = (char*)malloc(sizeof(char)*8);
    load_fast = (char*)malloc(sizeof(char)*8);
    store_fast = (char*)malloc(sizeof(char)*8);
    load_global = (char*)malloc(sizeof(char)*8);
    binary_add = (char*)malloc(sizeof(char)*8);
    binary_subtract = (char*)malloc(sizeof(char)*8);
    binary_multiply = (char*)malloc(sizeof(char)*8);
    binary_divide = (char*)malloc(sizeof(char)*8);
    inplace_add = (char*)malloc(sizeof(char)*8);
    pop_jump_if_true = (char*)malloc(sizeof(char)*8);
    pop_jump_if_false = (char*)malloc(sizeof(char)*8);
    jump_forward = (char*)malloc(sizeof(char)*8);
    jump_absolute = (char*)malloc(sizeof(char)*8);
    compare_op = (char*)malloc(sizeof(char)*8);
    call_function = (char*)malloc(sizeof(char)*8);
    return_value = (char*)malloc(sizeof(char)*8);

    strcpy(load_const, "00001100");
    strcpy(load_fast, "00001101");
    strcpy(store_fast, "00001111");
    strcpy(load_global, "00001110");
    strcpy(compare_op, "00000010");
    strcpy(pop_jump_if_false, "00110000");
    strcpy(pop_jump_if_true, "00110001");
    strcpy(jump_forward, "00110010");
    strcpy(jump_absolute, "00110011");
    strcpy(binary_add, "00100000");
    strcpy(binary_subtract, "00100001");
    strcpy(binary_multiply, "00100010");
    strcpy(binary_divide, "00100011");
    strcpy(inplace_add, "00101000");
    strcpy(call_function, "01100000");
    strcpy(return_value, "01100001");


    if((strcmp(comando, "LOAD_CONST")) == 0)
        return load_const;
    else if((strcmp(comando, "LOAD_FAST")) == 0)
        return load_fast;
    else if((strcmp(comando, "STORE_FAST")) == 0)
        return store_fast;
     else if((strcmp(comando, "LOAD_GLOBAL")) == 0)
         return load_global;
    else if((strcmp(comando, "BINARY_ADD")) == 0)
        return binary_add;
    else if((strcmp(comando, "BINARY_SUBTRACT")) == 0)
        return binary_subtract;
    else if((strcmp(comando, "BINARY_MULTIPLY")) == 0)
        return binary_multiply;
    else if((strcmp(comando, "BINARY_DIVIDE")) == 0)
        return binary_divide;
    else if((strcmp(comando, "INPLACE_ADD")) == 0)
        return inplace_add;
    else if((strcmp(comando, "POP_JUMP_IF_FALSE")) == 0)
        return pop_jump_if_false;
    else if((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0)
        return pop_jump_if_true;
    else if((strcmp(comando, "JUMP_FORWARD")) == 0)
        return jump_forward;
    else if((strcmp(comando, "JUMP_ABSOLUTE")) == 0)
        return jump_absolute;
    else if((strcmp(comando, "COMPARE_0P")) == 0)
        return compare_op;
    // else if((strcmp(comando, "SETUP_LOOP")) == 0)
    //     return 1;
    else if((strcmp(comando, "CALL_FUNCTION")) == 0)
        return call_function;
    else if((strcmp(comando, "RETURN_VALUE")) == 0)
        return return_value;
    // else if((strcmp(comando, "POP_BLOCK")) == 0)
    //     return 1;
}

char* verComparacao(int val){
    char *code;
    code = (char*)malloc(sizeof(char)*8);
    switch(val){
        case 0:           // igual
            strcpy(code, "00011000");
            break;
        case 1:          // menor
            strcpy(code, "00011001");
            break;
        case 2:          // maior
            strcpy(code, "00011010");
            break;
    }
    return code;
}
