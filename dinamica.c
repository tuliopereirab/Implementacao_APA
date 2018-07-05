#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _matrizCustos{
    char *passouPor;
    int custo;
};


// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
int **matriz;
int i, j;
struct _matrizCustos **matrizCustos;

//int** matrizCustos;
void gerarCustos(int ii, int k);
void criaMatrizCustos();
void imprimeMatriz();

void dinamica(char arquivo[]){
    int x, y;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    criaMatrizCustos();

    for(x=1;x<i;x++){
        for(y=0;y<i;y++){
            if((y+x) < i)
                gerarCustos(y, x);
        }
    }

    imprimeMatriz();

    system(EXIT_SUCCESS);
}

void gerarCustos(int ii, int k){
    char aux[10];
    if(k==1){
        //printf("Primeira!\n");
        sprintf(aux, "%i", ii);
        strcpy(matrizCustos[ii][ii+k].passouPor, aux);
        strcat(matrizCustos[ii][ii+k].passouPor, " ");
        matrizCustos[ii][ii+1].custo = matriz[ii][ii+1];
    }
    else{
        if((matrizCustos[ii][ii+(k-1)].custo + matrizCustos[ii+(k-1)][ii+k].custo) < matriz[ii][ii+k]){
            //printf("Soma!\n");
            sprintf(aux, "%i", ii+k);
            strcat(matrizCustos[ii][ii+k].passouPor, matrizCustos[ii][ii+(k-1)].passouPor);
            strcat(matrizCustos[ii][ii+k].passouPor, " ");
            strcat(matrizCustos[ii][ii+k].passouPor, aux);
            matrizCustos[ii][ii+k].custo = matrizCustos[ii][ii+(k-1)].custo + matrizCustos[ii+(k-1)][ii+k].custo;
        }else{
            //printf("Matriz original!\n");
            sprintf(aux, "%i", ii);
            strcpy(matrizCustos[ii][ii+k].passouPor, aux);
            strcat(matrizCustos[ii][ii+k].passouPor, " ");
            sprintf(aux, "%i", ii+k);
            strcat(matrizCustos[ii][ii+k].passouPor, aux);
            matrizCustos[ii][ii+k].custo = matriz[ii][ii+k];
        }
    }
}

void criaMatrizCustos(){
    int x, y;
    matrizCustos = (struct _matrizCustos**)malloc(sizeof(struct _matrizCustos*)*i);
    for(x=0;x<i;x++){
        matrizCustos[x] = (struct _matrizCustos*)malloc(sizeof(struct _matrizCustos)*i);
        for(y=0;y<i;y++){
            matrizCustos[x][y].custo = 0;
            matrizCustos[x][y].passouPor = malloc(sizeof(char)*i*4);
        }
    }

    printf("Matriz de custos criada...\n");
}

void imprimeMatriz(){
    int x, y;
    for(x=0;x<i;x++){
        for(y=0;y<i;y++)
            printf("%s ||", matrizCustos[x][y].passouPor);
        printf("\n");
    }
}
