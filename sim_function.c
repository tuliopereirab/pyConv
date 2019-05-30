#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_FUNC_WIDTH 8
#define ADDR_WIDTH 12

typedef struct _funcStack{
    char *TOSreturn;
    char *PCreturn;
}funcStack;

int return_value();
int call_func(char pc[], char tos[]);
int func_init();

int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);
int add_stack(char data[]);
int read_stack();
int pilha_init();
void changeTos(int newTos);
int verTos();

funcStack *func = NULL;
int tosFunc=0;

int func_init(){
    int i;
    if((func = (funcStack*)malloc(sizeof(funcStack)*pow(2,ADDR_FUNC_WIDTH))) == NULL)
        return -97;
    for(i=0; i<pow(2, ADDR_FUNC_WIDTH); i++){
        func[i].TOSreturn = (char*)malloc(sizeof(char)*ADDR_WIDTH);
        func[i].PCreturn = (char*)malloc(sizeof(char)*ADDR_WIDTH);
        strcpy(func[i].PCreturn, "000000000000");
        stpcpy(func[i].TOSreturn, "000000000000");
    }
    return 0;
}

int call_func(char pc[], char tos[]){
    if((tosFunc+1) >= pow(2, ADDR_FUNC_WIDTH))
        return -7;
    tosFunc++;
    strcpy(func[tosFunc].TOSreturn, tos);
    stpcpy(func[tosFunc].PCreturn, pc);
    return 0;
}

int return_value(){             // retorna o valor de PC
    int dataReturn;
    int status, statusReturn;
    char *TOSreturn, *PCreturn;
    if((tosFunc-1) < 0)
        return -8;
    TOSreturn = (char*)malloc(sizeof(char)*ADDR_WIDTH);
    PCreturn = (char*)malloc(sizeof(char)*ADDR_WIDTH);
    strcpy(TOSreturn, func[tosFunc].TOSreturn);
    strcpy(PCreturn, func[tosFunc].PCreturn);
    tosFunc--;
    if(atoi(TOSreturn) >= verTos())
        statusReturn = -1;          // não retorna dados
    else{
        dataReturn = read_stack();
        statusReturn = 0;           // retorna dados
    }
    changeTos(bin_to_dec(TOSreturn));     // faz a pilha retornar seu TOS
    if(statusReturn >= 0) // retorna dados
        status = add_stack(dec_to_bin(dataReturn, DATA_WIDTH));     // so retorna dados se houver
    return bin_to_dec(PCreturn);        // retorna novo valor de PC
}
