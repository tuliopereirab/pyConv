#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_FUNC_WIDTH 8
#define ADDR_WIDTH 12

// ---------------------------
// sim_apoio.c
int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);
//----------------------------
// sim_pilha.c
int add_stack(char data[]);
int read_stack();
int pilha_init();
void changeTos(int newTos);
int verTos();

int ula_arith(int sel){ // 0=add, 1=sub, 2=mult, 3=div
    int op1, op2, result;
    if(verTos() <= 1)
        return -9;
    op2 = read_stack();
    op1 = read_stack();
    switch(sel){
        case 0:
            add_stack(dec_to_bin(result=op1+op2, DATA_WIDTH));
            break;
        case 1:
            add_stack(dec_to_bin(result=op1-op2, DATA_WIDTH));
            break;
        case 2:
            add_stack(dec_to_bin(result=op1*op2, DATA_WIDTH));
            break;
        case 3:
            add_stack(dec_to_bin(result=op1/op2, DATA_WIDTH));
            break;
        default:
            add_stack(dec_to_bin(result=op1+op2, DATA_WIDTH));
    }
    if((result>pow(2,DATA_WIDTH)) || (result<0))
        return -10;
    else
        return 0;
}

int comp_op(int sel){   // 0:igual, 1:menor, 2:maior
    int op1, op2, result;
    if(verTos() <= 1)
        return -9;
    op2 = read_stack();
    op1 = read_stack();
    switch(sel){
        case 0:
            if(op2 == op1)
                return 1;
            else
                return 0;
            break;
        case 1:
            if(op1 < op2)
                return 1;
            else
                return 0;
            break;
        case 2:
            if(op1 > op2)
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
    }
}
