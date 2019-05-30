#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);
int check_number(char arg[]);
char *bitwise_op(char op1[], char op2[], int data_width, int sel);


int bin_to_dec(char bin[]){
    // copiado de https://www.sanfoundry.com/c-program-binary-number-into-decimal/
    int  num, binary_val, decimal_val = 0, base = 1, rem;
    binary_val = atoi(bin);
    num = binary_val;
    while (num > 0)
    {
        rem = num % 10;
        decimal_val = decimal_val + rem * base;
        num = num / 10 ;
        base = base * 2;
    }
    return decimal_val;
}


char *dec_to_bin(int n, int tam){       // copiado de https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary

   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(tam+1);

   for (c = tam-1; c >= 0 ; c--){
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';
   return pointer;
}

int check_number(char arg[]){
    int i, tam = strlen(arg);
    for(i=0; i<tam; i++){
        if(isdigit(arg[i]) == 0)
            return -1;      // não é um número
    }
    return 0;
}

char *bitwise_op(char op1[], char op2[], int data_width, int sel){
    int i;
    char *result;
    int x1;
    result = (char*)malloc(sizeof(char)*data_width);
    for(i=0; i<data_width; i++){
        switch(sel){
            case 4:
                if((op1[i] == '1') && (op2[i] == '1'))
                    result[i] = '1';
                else
                    result[i] = '0';
                break;
            case 5:
                if((op1[i] == '1') || (op2[i] == '1'))
                    result[i] = '1';
                else
                    result[i] = '0';
                break;
            case 6:
                if(((op1[i] == '1') && (op2[i] == '1')) || ((op1[i] == '0') && (op2[i] == '0')))
                    result[i] = '0';
                else
                    result[i] = '1';
                break;
            default:
                if((op1[i] == '1') && (op2[i] == '1'))
                    result[i] = '1';
                else
                    result[i] = '0';
        }
    }
    return result;
}
