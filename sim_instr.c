#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_FUNC_WIDTH 8
#define ADDR_WIDTH 12

int regComp=-1;
int pc=0;

// ---------------------------
// sim_apoio.c
int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);
int check_number(char arg[]);
//----------------------------
// sim_pilha.c
int add_stack(char data[]);
int read_stack();
int pilha_init();
void changeTos(int newTos);
int verTos();
//----------------------------
// sim_function.c
int return_value();
int call_func(char pc[], char tos[]);
int func_init();
//----------------------------
// sim_memExt.c
int read_memory(char addr[]);
int add_memory(char data[], char addr[]);
int memory_init();
//----------------------------
// sim_ula.c
int ula_arith(int sel);
int comp_op(int sel);
//---------------------------
// sim_error.c
void print_error(int code);
//---------------------------
// controle_variaveis.c
char *decimal_to_binary_addr(int n);
char *decimal_to_binary_code(int n);
char *busca_variavel(char chave[]);
int adicionar_variavel(char chave[]);
int verifica_variavel(char variavel[]);

#define MEMORY_SIZE 4096
#define DATA_WIDTH 8
#define ADDR_FUNC_WIDTH 8
#define ADDR_WIDTH 12


int load_const(char arg[]){
    int argumento, status;
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if(((argumento = atoi(arg)) < pow(2, DATA_WIDTH)) && (argumento >= 0))
        status = add_stack(dec_to_bin(argumento, DATA_WIDTH));
    else
        status = -2;
    if(status < 0){
        print_error(status);
        return -12;
    }else{
        pc++;
        return pc;
    }
}

int load_fast(char arg[]){
    int data, stat;
    if((stat = verifica_variavel(arg)) == 0){  // verifica se existe
        if((data = read_memory(dec_to_bin(atoi(busca_variavel(arg)), ADDR_WIDTH))) < 0){
            print_error(data);
            return -12;
        }else
            if((stat = add_stack(dec_to_bin(data, DATA_WIDTH))) < 0){
                print_error(stat);
                return -12;
            }else{
                pc = pc+2;
                return pc;
            }
    }else{
        printf("var não existe: %i\n", stat);
        print_error(stat);
        return -12;
    }
}

int store_fast(char arg[]){
    int data, stat;
    if((data = read_stack()) < 0){
        print_error(data);
        return -12;
    }else
        if((stat = add_memory(dec_to_bin(data, DATA_WIDTH), dec_to_bin(atoi(busca_variavel(arg)), ADDR_WIDTH))) < 0){
            print_error(stat);
            return -12;
        }else{
            pc = pc+2;
            return pc;
        }
}

int pop_true(char arg[]){
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if(regComp < 0){
        print_error(-13);
        return -12;
    }else if(regComp == 1){
        if((atoi(arg) < pow(2, ADDR_WIDTH)) && (atoi(arg)>=0)){
            pc = atoi(arg);
            return pc;
        }else{
            print_error(-14);
            return -12;
        }
    }
}

int pop_false(char arg[]){
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if(regComp < 0){
        print_error(-13);
        return -12;
    }else if(regComp == 1){
        if((atoi(arg) < pow(2, ADDR_WIDTH)) && (atoi(arg)>=0)){
            pc = atoi(arg);
            return pc;
        }else{
            print_error(-14);
            return -12;
        }
    }
}

int jump_absolute(char arg[]){
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if((atoi(arg) >= 0) && (atoi(arg) < pow(2, ADDR_WIDTH))){
        pc = atoi(arg);
        return pc;
    }else{
        print_error(-14);
        return -12;
    }
}

int jump_forward(char arg[]){
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if(((atoi(arg)+pc) >= 0) && ((atoi(arg)+pc) < pow(2, ADDR_WIDTH))){
        pc = pc + atoi(arg);
        return pc;
    }else{
        print_error(-14);
        return -12;
    }
}

int binary(int sel){
    int stat;
    if((stat = ula_arith(sel)) < 0){
        print_error(stat);
        return -20;     // retorna que ocorreu um warning
    }else{
        pc++;
        return pc;
    }
}

int compare_op(char arg[]){
    int comp;
    if((comp = comp_op(atoi(arg))) < 0){
        print_error(comp);
        return -12;
    }else{
        pc++;
        regComp = comp;
        return pc;
    }
}

int call_function(char arg[]){
    int stat;
    if(check_number(arg) != 0){
        print_error(-1);
        return -12;
    }
    if((atoi(arg)>= pow(2, ADDR_WIDTH)) || (atoi(arg) < 0)){
        print_error(-6);
        return -12;
    }
    if(pc+2>=pow(2, ADDR_WIDTH)){
        print_error(-16);
        return -12;
    }
    if((stat = call_func(dec_to_bin(pc+2, ADDR_WIDTH), dec_to_bin(verTos(), ADDR_WIDTH))) < 0){
        print_error(stat);
        return -12;
    }else{
        pc = atoi(arg);
        return pc;
    }
}

int ret_value(){
    int newPc;
    if((newPc = return_value()) < 0){
        print_error(newPc);
        return -12;
    }else{
        pc = newPc;
        return pc;
    }
}
