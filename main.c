#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv){
    char *hexa;
    hexa = decToHex(255);
    printf("Valor hexadecimal: %s\n", hexa);
}


char* decToHex(int num){
    char hexa[5];
    sprintf(hexa, "%x", num);
    return hexa;
}
