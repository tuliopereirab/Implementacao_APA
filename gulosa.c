#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INTERNAS
void execGulosa(int atual, int vetVerif[]);
int verificaSolucao(int vetVerif[], int prox);
int *zerarVet(int vetVerif[]);
int verificaFinal(int vetVerif[]);
// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
int **matriz;
int i, j;
int soma;

void gulosa(char arquivo[]){
    int x, y;
    int *vetVerifica;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    vetVerifica = malloc(sizeof(int)*i);
    vetVerifica = zerarVet(vetVerifica);

    for(x=0; x<i; x++){
        for(y=0; y<i; y++)
            vetVerifica[y] = 0;
        soma = 0;
        printf("Solução partindo de %i: %i", x, x);
        vetVerifica[x] = 1;
        execGulosa(x, vetVerifica);
        printf("\tSOMA: %i", soma);
        printf("\n");
    }

    system(EXIT_SUCCESS);
}

void execGulosa(int atual, int vetVerif[]){
    int x;
    int menorPos, menorVal=0;
    int statusInicial = 0;
    int status;
    for(x=0;x<j;x++){
        if(atual != x){
            if(statusInicial == 0){
                status = verificaSolucao(vetVerif, x);
                if(status == 1){
                    menorVal = matriz[atual][x];
                    menorPos = x;
                    status = 1;
                }
            }else{
                if(matriz[atual][x] < menorVal){
                    status = verificaSolucao(vetVerif, x);
                    if(status == 1){
                        menorVal = matriz[atual][x];
                        menorPos = x;
                    }
                }
            }
        }
    }
    soma = soma + menorVal;
    vetVerif[menorPos] = 1;
    printf(" %i", menorPos);
    if(verificaFinal(vetVerif) == 0)  // nao acabou
        execGulosa(menorPos, vetVerif);
}

int verificaSolucao(int vetVerif[], int prox){
    if(vetVerif[prox] == 0)
        return 1;   // não foi acessado ainda, pode ser solução
    else
        return 0;   // já foi acessado, não é viável para solução
}


int *zerarVet(int vetVerif[]){
    int x;
    for(x=0; x<i; x++)
        vetVerif[x] = 0;
    soma = 0;
    return vetVerif;
}

int verificaFinal(int vetVerif[]){
    int x, status=1;
    for(x=0;x<i;x++)
        if(vetVerif[x] == 0)   // nao finalizou
            status = 0;
    return status;
}
