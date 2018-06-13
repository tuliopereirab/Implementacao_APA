#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();

void gulosa(char arquivo[]){
    int i, j, x, y;
    int **matriz;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();


    system(EXIT_SUCCESS);
}
