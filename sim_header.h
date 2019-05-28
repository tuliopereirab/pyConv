#include <stdio.h>
// #include "sim_error.c"
// #include "sim_function.c"
// #include "sim_main.c"
#include "sim_memExt.c"
#include "sim_pilha.c"
// #include "sim_ula.c"
// #include "controle_variaveis.c"
#include "sim_apoio.c"


// ---------------------------
// sim_apoio.c
int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);
//----------------------------
// sim_pilha.c
int add_stack(char data[]);
int read_stack();
int pilha_init();
