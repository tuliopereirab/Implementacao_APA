#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();

void dinamica(char arquivo[]){
    int **matriz;
    int i, j, x, y;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();


    system(EXIT_SUCCESS);
}
