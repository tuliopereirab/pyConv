#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int bin_to_dec(char bin[]);
char *dec_to_bin(int n, int tam);

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


char *dec_to_bin(int n, int tam)       // copiado de https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
{
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
