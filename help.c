#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ADDR_LENGTH 4096
#define MAX_DATA_VALUE 255

void help_init();
void help_loadConst();
void help_loadFast();
void help_storeFast();
void help_binary();
void help_compareOp();
void help_popJump();
void help_jumpForward();
void help_jumpAbsolute();
void help_callFunc();
void help_returnValue();
void help_inicializacao();

void help_init(char command[]){

    printf("---------------------------\n");
    printf("\tHELP CENTER\n");
    if((strcmp(command, "LOAD_CONST")) == 0)
        help_loadConst();
    else if((strcmp(command, "LOAD_FAST")) == 0)
        help_loadFast();
    else if((strcmp(command, "STORE_FAST")) == 0)
        help_storeFast();
    else if((strcmp(command, "COMPARE_OP")) == 0)
        help_compareOp();
    else if((strcmp(command, "BINARY_ADD")) == 0)
        help_binary();
    else if((strcmp(command, "BINARY_SUBTRACT")) == 0)
        help_binary();
    else if((strcmp(command, "BINARY_MULTIPLY")) == 0)
        help_binary();
    else if((strcmp(command, "BINARY_DIVIDE")) == 0)
        help_binary();
    else if((strcmp(command, "POP_JUMP_IF_TRUE")) == 0)
        help_popJump();
    else if((strcmp(command, "POP_JUMP_IF_FALSE")) == 0)
        help_popJump();
    else if((strcmp(command, "JUMP_FORWARD")) == 0)
        help_jumpForward();
    else if((strcmp(command, "JUMP_ABSOLUTE")) == 0)
        help_jumpAbsolute();
    else if((strcmp(command, "CALL_FUNCTION")) == 0)
        help_callFunc();
    else if((strcmp(command, "RETURN_VALUE")) == 0)
        help_returnValue();
    else
        printf("Comando inválido ou não suportado.\n");

    printf("---------------------------\n");
}

void help_loadConst(){
    printf("Comando: LOAD_CONST\n");
    printf("Descrição: responsável por adicionar um valor diretamente na pilha.\n");
    printf("Formatação: 'LOAD_CONST [valor_inteiro_positivo]'\n");
    printf("Maior valor suportado: %i.\n", MAX_DATA_VALUE);
}

void help_loadFast(){
    printf("Comando: LOAD_FAST\n");
    printf("Descrição: responsável por ler uma variável da memória.\n");
    printf("Formatação: 'LOAD_FAST [nome_variavel]'\n");
    //printf("Maior valor suportado: %i.\n", MAX_ADDR_LENGTH);
}

void help_storeFast(){
    printf("Comando: STORE_FAST\n");
    printf("Descrição: responsável por salvar uma variável na memória.\n");
    printf("Formatação: 'STORE_FAST [nome_variavel]'\n");
    //printf("Maior valor suportado: %i.\n", MAX_ADDR_LENGTH);
}

void help_binary(){
    printf("Comando: BINARY_\n");
    printf("Descrição: realiza uma operação aritmética entre os dois valores do topo da pilha. O resultado é retornado para a pilha.\n");
    printf("Formatação: 'BINARY_[operacao]'\n");
    printf("Operações possíveis: \n\tBINARY_ADD -> soma\n\tBINARY_SUBTRACT -> subtração\n\tBINARY_MULTIPLY -> multiplicação\n\tBINARY_DIVIDE -> divisão\n");
    printf("Não utiliza argumento.\n");
}

void help_compareOp(){
    printf("Comando: COMPARE_OP\n");
    printf("Descrição: realiza uma comparação, informada como argumento, entre os dois valores no topo da pilha. O resultado é retornado para o regComp.\n");
    printf("Formatação: 'COMPARE_OP [tipo_comparacao]'\n");
    printf("Tipos de comparações: \n\t0 -> igual\n\t1 -> menor que\n\t2 -> maior que\n");
}

void help_popJump(){
    printf("Comando: POP_JUMP_IF_\n");
    printf("Descrição: utiliza o resultado da comparação anterior para realizar um desvio.\n");
    printf("Formatação: 'POP_JUMP_IF_[condicao] [endereco_inteiro_positivo]'\n");
    printf("Condição: \n\tTRUE -> verdadeiro\n\tFALSE -> falso\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_jumpForward(){
    printf("Comando: JUMP_FORWARD\n");
    printf("Descrição: realiza um desvio incrementando o valor de PC com o valor de delta por argumento.\n");
    printf("Formatação: 'JUMP_FORWARD [delta]'\n");
    printf("Delta: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_jumpAbsolute(){
    printf("Comando: JUMP_ABSOLUTE\n");
    printf("Descrição: realiza um desvio substituindo o valor de PC pelo endereço no argumento.\n");
    printf("Formatação: 'JUMP_ABSOLUTE [endereco]'\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_callFunc(){
    printf("Comando: CALL_FUNCTION\n");
    printf("Descrição: realiza um desvio para o endereço passado por argumento e salva o valor de PC anterior para futuro retorno.\n");
    printf("Formatação: 'CALL_FUNCTION [endereco]'\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_returnValue(){
    printf("Comando: RETURN_VALUE\n");
    printf("Descrição: realiza um retorno para o valor de PC salvo na função CALL_FUNCTION e retorna o valor do topo da pilha atual para o novo topo.\n");
    printf("Formatação: 'RETURN_VALUE'\n");
    printf("Não utiliza argumento.\n");
}

void help_inicializacao(){
    printf("Ao inicializar o sistema, deve-se escolher o tipo de arquivo a ser gerado no final.\n");
    printf("Por padrão, geras-se um arquivo '.mem', caso o outro não seja escolhido.\n");
    printf("Para escolher, utilize:\n\t'./Compilador -mif'\n");
}
