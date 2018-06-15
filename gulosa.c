#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _solucao{
    char *stringSolucao;
    int soma;
};

// INTERNAS
void execGulosa(int atual, int vetVerif[], int valSolucao);
int verificaSolucao(int vetVerif[], int prox);
int *zerarVet(int vetVerif[]);
int verificaFinal(int vetVerif[]);
int verifMelhorSolucao();
// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
int **matriz;
int i, j;
int soma;
struct _solucao *solucao;



void gulosa(char arquivo[]){
    int x, y;
    int *vetVerifica;
    char valor[10];
    int melhorSol;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    vetVerifica = malloc(sizeof(int)*i);
    vetVerifica = zerarVet(vetVerifica);

    solucao = (struct _solucao*)malloc(sizeof(struct _solucao)*i);
    for(x=0;x<i;x++)
        solucao[x].stringSolucao = malloc(sizeof(char)*5*i);


    for(x=0; x<i; x++){
        vetVerifica = zerarVet(vetVerifica);
        soma = 0;
        printf("Solução partindo de %i: %i", x, x);
        //itoa(x,valor,10);
        sprintf(valor, "%i", x);
        strcpy(solucao[x].stringSolucao, valor);
        strcat(solucao[x].stringSolucao, " ");
        vetVerifica[x] = 1;
        execGulosa(x, vetVerifica, x);
        printf("\tSOMA: %i", soma);
        printf("\n");
    }

    melhorSol = verifMelhorSolucao();
    printf("--------------------\n");
    printf("MELHOR SOLUCAO: \n");
    printf("%s\nSOMA: %i\n", solucao[melhorSol].stringSolucao, solucao[melhorSol].soma);
    printf("--------------------\n");

    system(EXIT_SUCCESS);
}

void execGulosa(int atual, int vetVerif[], int valSolucao){
    int x;
    int menorPos, menorVal=0;
    int statusInicial = 0;
    int status;
    char valor[10];
    for(x=0;x<j;x++){
        if(atual != x){
            if(statusInicial == 0){
                status = verificaSolucao(vetVerif, x);
                if(status == 1){
                    menorVal = matriz[atual][x];
                    menorPos = x;
                    status = 1;
                    statusInicial = 1;
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
    sprintf(valor, "%i", menorPos);
    strcat(solucao[valSolucao].stringSolucao, valor);
    strcat(solucao[valSolucao].stringSolucao, " ");
    solucao[valSolucao].soma = soma;
    printf(" %i", menorPos);
    if(verificaFinal(vetVerif) == 0)  // nao acabou
        execGulosa(menorPos, vetVerif, valSolucao);
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

int verifMelhorSolucao(){
    int mSoma, mPos, init=0;
    int x;
    for(x=0; x<i; x++){
        if(init == 0){
            mSoma = solucao[x].soma;
            mPos = x;
            init = 1;
        }else{
            if(solucao[x].soma < mSoma){
                mSoma = solucao[x].soma;
                mPos = x;
            }
        }
    }
    return mPos;
}
