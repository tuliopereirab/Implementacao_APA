#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//EXTERNAS

void gerar(char entI[], char entJ[], char arquivo[]){
    int i, j, x, y, z;
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

    srand((unsigned)time(NULL));  // copiado internet: https://www.cprogressivo.net/2013/03/Como-gerar-numeros-aleatorios-em-C-com-a-rand-srand-e-seed.html
    for(x=0; x<i; x++){
        for(y=0; y<j; y++){
            if(x == y){
                matriz[x][y] = 0;
            }else{
                matriz[x][y] = rand() % 500;
                matriz[y][x] = matriz[x][y];
                //statusZero = rand() % 2;
                statusZero = 0;

                if(statusZero == 1){
                    matriz[x][y] = 0;
                    matriz[y][x] = 0;
                }
            }
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
