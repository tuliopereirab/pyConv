#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_error(int code);

int ret_value();
int call_function(char arg[]);
int compare_op(char arg[]);
int binary(int sel);
int jump_forward(char arg[]);
int jump_absolute(char arg[]);
int pop_false(char arg[]);
int pop_true(char arg[]);
int store_fast(char arg[]);
int load_fast(char arg[]);
int load_const(char arg[]);

int memory_init();
int func_init();
int pilha_init();
int check_number(char arg[]);

int init_simulator();
int simulator(char comando[], char argumento[]);

//  int main(){
//      char cmd[20], arg[30];
//      int stat;
//  init_simulator();
//      while(1){
//          printf("Comando: ");
//          scanf("%s", cmd);
//          scanf("%s", arg);
//          stat = simulator(cmd, arg);
//          printf("Status: %i\n", stat);
//      }
// }

int init_simulator(){
    int status;
    status = pilha_init();
    if(status == 0)
        status = memory_init();
    if(status == 0)
        status = func_init();
    if(status < 0)
        print_error(status);
    else
        return 0;
}

int simulator(char comando[], char argumento[]){    // op binary: 0:add; 1:sub; 2:mult; 3:div
    //printf("Recebido: %s\t%s\n", comando, argumento);
    if((strcmp(comando, "LOAD_CONST")) == 0)
        return load_const(argumento);
    else if((strcmp(comando, "LOAD_FAST")) == 0)
        return load_fast(argumento);
    else if((strcmp(comando, "STORE_FAST")) == 0)
        return store_fast(argumento);
    else if((strcmp(comando, "POP_JUMP_IF_TRUE")) == 0)
        return pop_true(argumento);
    else if((strcmp(comando, "POP_JUMP_IF_FALSE")) == 0)
        return pop_false(argumento);
    else if((strcmp(comando, "JUMP_ABSOLUTE")) == 0)
        return jump_absolute(argumento);
    else if((strcmp(comando, "JUMP_FORWARD")) == 0)
        return jump_forward(argumento);
    else if((strcmp(comando, "BINARY_ADD")) == 0)
        return binary(0);
    else if((strcmp(comando, "BINARY_SUBTRACT")) == 0)
        return binary(1);
    else if((strcmp(comando, "BINARY_MULTIPLY")) == 0)
        return binary(2);
    else if((strcmp(comando, "BINARY_DIVIDE")) == 0)
        return binary(3);
    else if((strcmp(comando, "BINARY_AND")) == 0)
        return binary(4);
    else if((strcmp(comando, "BINARY_OR")) == 0)
        return binary(5);
    else if((strcmp(comando, "BINARY_XOR")) == 0)
        return binary(6);
    else if((strcmp(comando, "UNARY_NOT")) == 0)
        return binary(7);       // not
    else if((strcmp(comando, "COMPARE_OP")) == 0)
        return compare_op(argumento);
    else if((strcmp(comando, "CALL_FUNCTION")) == 0)
        return call_function(argumento);
    else if((strcmp(comando, "RETURN_VALUE")) == 0)
        return ret_value();
    else
        return -17;
}
