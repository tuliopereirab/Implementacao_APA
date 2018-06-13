#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iGlob, jGlob;

int **lerArquivo(char arquivo[]){
    int i, j, x, y;
    int **matriz;
    char carac;
    int op = 0;
    FILE *arq;
    printf("Abrindo arquivo '%s'...\n", arquivo);
    arq = fopen(arquivo, "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo solicitado. Verifique o arquivo e tente novamente.\n");
        system(EXIT_SUCCESS);
    }
    i = 0;
    j = 0;

    printf("Lendo arquivo '%s'...\n", arquivo);
    carac = fgetc(arq);
    while(carac != EOF){
        if((carac == ' ') && (op == 0))
            j++;
        else if(carac == '\n'){
            if(op == 0){
                op = 1;
                //j++;
            }
            i++;
        }
        carac = fgetc(arq);
    }
    //-------------------------------------
    //TROCAR POR FSEEK (falta net pra aprender a usar)
    fclose(arq);
    arq = fopen(arquivo, "r");
    // ------------------------------------


    matriz = (int**)malloc(sizeof(int*)*i);
    for(x=0; x<i; x++){
        matriz[x] = (int*)malloc(sizeof(int)*j);
        for(y=0;y<j;y++){
            if(y==0)
                fscanf(arq, "%i", &matriz[x][y]);
            else
                fscanf(arq, " %i", &matriz[x][y]);
        }
    }

    printf("Arquivo '%s' lido com sucesso!\n", arquivo);

    iGlob = i;
    jGlob = j;

    return matriz;
}

int retI(){
    return iGlob;
}
int retJ(){
    return jGlob;
}
