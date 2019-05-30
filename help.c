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
    if(((strcmp(command, "LOAD_CONST")) == 0) || ((strcmp(command, "lconst")) == 0))
        help_loadConst();
    else if(((strcmp(command, "LOAD_FAST")) == 0) || ((strcmp(command, "lfast")) == 0))
        help_loadFast();
    else if(((strcmp(command, "STORE_FAST")) == 0) || ((strcmp(command, "sfast")) == 0))
        help_storeFast();
    else if(((strcmp(command, "COMPARE_OP")) == 0) || ((strcmp(command, "cop")) == 0))
        help_compareOp();
    else if(((strcmp(command, "BINARY_ADD")) == 0) || ((strcmp(command, "badd")) == 0))
        help_binary();
    else if(((strcmp(command, "BINARY_SUBTRACT")) == 0) || ((strcmp(command, "bsub")) == 0))
        help_binary();
    else if(((strcmp(command, "BINARY_MULTIPLY")) == 0) || ((strcmp(command, "bmult")) == 0))
        help_binary();
    else if(((strcmp(command, "BINARY_DIVIDE")) == 0) || ((strcmp(command, "bdiv")) == 0))
        help_binary();
    else if(((strcmp(command, "POP_JUMP_IF_TRUE")) == 0) || ((strcmp(command, "ptrue")) == 0))
        help_popJump();
    else if(((strcmp(command, "POP_JUMP_IF_FALSE")) == 0) || ((strcmp(command, "pfalse")) == 0))
        help_popJump();
    else if(((strcmp(command, "JUMP_FORWARD")) == 0) || ((strcmp(command, "jfor")) == 0))
        help_jumpForward();
    else if(((strcmp(command, "JUMP_ABSOLUTE")) == 0) || ((strcmp(command, "jabs")) == 0))
        help_jumpAbsolute();
    else if(((strcmp(command, "CALL_FUNCTION")) == 0) || ((strcmp(command, "cfunc")) == 0))
        help_callFunc();
    else if(((strcmp(command, "RETURN_VALUE")) == 0) || ((strcmp(command, "rval")) == 0))
        help_returnValue();
    else
        printf("Comando inválido ou não suportado.\n");

    printf("---------------------------\n");
}

void help_loadConst(){
    printf("Comando Assembly: LOAD_CONST\n");
    printf("Comando do conversor: 'lconst'\n");
    printf("Descrição: responsável por adicionar um valor diretamente na pilha.\n");
    printf("Formatação: 'lconst [valor_inteiro_positivo]'\n");
    printf("Maior valor suportado: %i.\n", MAX_DATA_VALUE);
}

void help_loadFast(){
    printf("Comando Assembly: LOAD_FAST'\n");
    printf("Comando do conversor: 'lfast\n");
    printf("Descrição: responsável por ler uma variável da memória.\n");
    printf("Formatação: 'lfast [nome_variavel]'\n");
    //printf("Maior valor suportado: %i.\n", MAX_ADDR_LENGTH);
}

void help_storeFast(){
    printf("Comando Assembly: STORE_FAST'\n");
    printf("Comando do conversor: 'sfast\n");
    printf("Descrição: responsável por salvar uma variável na memória.\n");
    printf("Formatação: 'sfast [nome_variavel]'\n");
    //printf("Maior valor suportado: %i.\n", MAX_ADDR_LENGTH);
}

void help_binary(){
    printf("Comando Assembly: BINARY_\n");
    printf("Comando do conversor: 'badd', 'bsub', 'bmult' ou 'bdiv'\n");
    printf("Descrição: realiza uma operação aritmética entre os dois valores do topo da pilha. O resultado é retornado para a pilha.\n");
    printf("Formatação: 'b[operacao]'\n");
    printf("Operações possíveis: \n\t'badd' -> soma\n\t'bsub' -> subtração\n\t'bmult' -> multiplicação\n\t'bdiv' -> divisão\n");
    printf("Não utiliza argumento.\n");
}

void help_compareOp(){
    printf("Comando Assembly: COMPARE_OP\n");
    printf("Comando do conversor: 'cop'\n");
    printf("Descrição: realiza uma comparação, informada como argumento, entre os dois valores no topo da pilha. O resultado é retornado para o regComp.\n");
    printf("Formatação: 'cop [tipo_comparacao]'\n");
    printf("Tipos de comparações: \n\t0 -> igual\n\t1 -> menor que\n\t2 -> maior que\n");
}

void help_popJump(){
    printf("Comando Assembly: POP_JUMP_IF_\n");
    printf("Comando do conversor: 'ptrue' ou 'pfalse'\n");
    printf("Descrição: utiliza o resultado da comparação anterior para realizar um desvio.\n");
    printf("Formatação: 'p[condicao] [endereco_inteiro_positivo]'\n");
    printf("Condição: \n\t'ptrue' -> verdadeiro\n\t'pfalse' -> falso\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_jumpForward(){
    printf("Comando Assembly: JUMP_FORWARD\n");
    printf("Comando do conversor: 'jfor'\n");
    printf("Descrição: realiza um desvio incrementando o valor de PC com o valor de delta por argumento.\n");
    printf("Formatação: 'jfor [delta]'\n");
    printf("Delta: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_jumpAbsolute(){
    printf("Comando Assembly: JUMP_ABSOLUTE\n");
    printf("Comando do conversor: 'jabs'\n");
    printf("Descrição: realiza um desvio substituindo o valor de PC pelo endereço no argumento.\n");
    printf("Formatação: 'jabs [endereco]'\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_callFunc(){
    printf("Comando Assembly: CALL_FUNCTION\n");
    printf("Comando do conversor: 'cfunc'\n");
    printf("Descrição: realiza um desvio para o endereço passado por argumento e salva o valor de PC anterior para futuro retorno.\n");
    printf("Formatação: 'cfunc [endereco]'\n");
    printf("Endereço: valor inteiro positivo menor que %i.\n", MAX_ADDR_LENGTH);
}

void help_returnValue(){
    printf("Comando Assembly: RETURN_VALUE\n");
    printf("Comando do conversor: 'rval'\n");
    printf("Descrição: realiza um retorno para o valor de PC salvo na função CALL_FUNCTION e retorna o valor do topo da pilha atual para o novo topo.\n");
    printf("Formatação: 'rval'\n");
    printf("Não utiliza argumento.\n");
}

void help_inicializacao(){
    printf("-----------------------------------\n\tHELP\n-----------------------------------\n");
    printf("Gerar apenas .mem: \t './Compilador -mem'\n");
    printf("Gerar apenas .mif: \t './Compilador -mif'\n");
    printf("Gerar ambos: \t\t './Compilador'\n");
    printf("----------------------------------------\n");
}
