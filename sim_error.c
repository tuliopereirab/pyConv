#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_FUNC_WIDTH 8
#define ADDR_WIDTH 12

void print_error(int code){
    switch(code){
        case -2:
            printf("error %i: Largura de dado incorreta.\n", code);
            break;
        case -3:
            printf("error %i: Largura de endereço incorreta.\n", code);
            break;
        case -4:
            printf("error %i: Ponteiro do topo da pilha ficará negativo.\n\tUtilize adicione algo na pilha antes de remover.\n", code);
            break;
        case -5:
            printf("error %i: Ponteiro do topo da pilha ultrapassará limite superior.\n\tRetire algo da pilha antes de adicionar algo.\n", code);
            break;
        case -6:
            printf("error %i: Endereço de memória está fora do intervalo esperado (0 a %.0lf).\n", code, pow(2, ADDR_WIDTH));
            break;
        case -7:
            printf("error %i: Ponteiro do topo da pilha de funções ultrapassará limite superior.\n\tExecute 'RETURN_VALUE' antes de utilizar 'CALL_FUNCTION'.\n", code);
            break;
        case -8:
            printf("error %i: Ponteiro do topo da pilha de funções ficará negativo.\n\tUtilize 'CALL_FUNCTION' antes de 'RETURN_VALUE'.\n", code);
            break;
        case -9:
            printf("error %i: Pilha não suporta as duas leituras exigidas. Certifique-se que existam dois dados na pilha.\n", code);
            break;
        case -10:
            printf("warning %i: Resultando com Overflow.\n", code);
            break;
        case -11:
            printf("error %i: Instrução inválida.\n", code);
            break;
        case -12:
            printf("error %i: Algum erro foi encontrado no simulador. Instrução não executada.\n", code);
            break;
        case -13:
            printf("error %i: Resultado da comparação inválido.\n\tExecute uma comparação antes de um desvio condicional.\n", code);
            break;
        case -14:
            printf("error %i: Valor do endereço fora do invervalo esperado (0 a %.0lf).\n", code, pow(2, ADDR_WIDTH));
            break;
        case -15:
            printf("error %i: Soma entre PC atual e argumento da instrução ultrapassam valor máximo de %.0lf.\n", code, pow(2, ADDR_WIDTH));
            break;
        case -16:
            printf("error %i: Valor de PC ficará acima do máximo suportado.\n", code);
            break;
        case -97:
            printf("error %i: Erro ao alocar pilha de funções.\n", code);
            break;
        case -98:
            printf("error %i: Erro ao alocar pilha principal.\n", code);
            break;
        case -99:
            printf("error %i: Erro ao alocar memória externa.\n", code);
            break;
        default:
            printf("%i: Erro desconhecido.\n", code);
    }
}
