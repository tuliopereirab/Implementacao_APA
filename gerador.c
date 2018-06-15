#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//EXTERNAS

void gerar(char entI[], char entJ[], char arquivo[]){
    int i, j, x, y;
    int status;
    int **matriz;
    int statusZero;
    FILE *arq;
    i = atoi(entI);
    j = atoi(entJ);

    printf("Gerando matriz [%i][%i]...\n", i, j);

    matriz = (int**)malloc(sizeof(int*)*i);
    for(x=0; x<i; x++)
        matriz[x] = (int*)malloc(sizeof(int)*j);

    for(x=0; x<i; x++){
        for(y=0; y<j; y++){
            matriz[x][y] = rand() % 1000;
            statusZero = rand() % 3;

            /*if(statusZero == 1)
                matriz[x][y] = 0;*/
        }
    }

    printf("Criando arquivo '%s'...\n", arquivo);
    arq = fopen(arquivo, "w+");
    for(x=0;x<i;x++){
        for(y=0;y<j; y++){
            fprintf(arq, " %i", matriz[x][y]);
        }
        fprintf(arq, "\n");
    }

    //status = criarArquivo(i, j, matriz, arquivo);
    //if(status == 1){
        printf("Arquivo '%s' criado com sucesso!\n", arquivo);
    //}
    system(EXIT_SUCCESS);
}
