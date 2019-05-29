#include <stdio.h>
#include "sim_error.c"
#include "sim_function.c"
#include "sim_main.c"
#include "sim_memExt.c"
#include "sim_pilha.c"
#include "sim_ula.c"
//#include "controle_variaveis.c"
#include "sim_apoio.c"
#include "sim_instr.c"


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
//----------------------------
// sim_instr.c
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
//---------------------------
// sim_error.c
void print_error(int code);
// //---------------------------
// // controle_variaveis.c
// char *decimal_to_binary_addr(int n);
// char *decimal_to_binary_code(int n);
// char *busca_variavel(char chave[]);
// int adicionar_variavel(char chave[]);
// int verifica_variavel(char variavel[]);
