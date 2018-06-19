#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _solucao{
    char *stringSolucao;
    int soma;
};

// INTERNAS
void execGulosa(int atual, int valSolucao, char solucaoVertice[]);
int verificaSolucao(int prox);
void zerarVet();
int verificaFinal();
void mostrarSolucoes();
int verifMelhorSolucao();
// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();

// GLOBAIS
int **matriz;
int i, j;
int soma;
struct _solucao *solucao;
int nSolucoes=0;
int *vetVerifica;



void gulosa(char arquivo[]){
    int x, y;
    //int *vetVerifica;
    char valor[10];
    int melhorSol;
    char *solucaoVertice;
    solucaoVertice = malloc(sizeof(char)*5*i);
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    vetVerifica = malloc(sizeof(int)*i);
    zerarVet();
    printf("Encontrando soluções...\n");
    printf("------------------------------------\n");
    //solucao = (struct _solucao*)malloc(sizeof(struct _solucao)*i);
    //for(x=0;x<i;x++)
        //solucao[x].stringSolucao = malloc(sizeof(char)*5*i);


    for(x=0; x<i; x++){
        printf("Foi for!\n");
        zerarVet();
        soma = 0;
        printf("Solução partindo de %i: %i", x, x);
        //itoa(x,valor,10);
        sprintf(valor, "%i", x);
        strcpy(solucaoVertice, valor);
        strcat(solucaoVertice, " ");
        vetVerifica[x] = 1;
        execGulosa(x, x, solucaoVertice);
        //printf("\tSOMA: %i", soma);
        printf("\n");
    }
    printf("------------------------------------\n");
    printf("Numero de soluções: %i\n", nSolucoes);
    if(nSolucoes != 0){
        melhorSol = verifMelhorSolucao();
        mostrarSolucoes();
        printf("--------------------\n");
        printf("MELHOR SOLUCAO: \n");
        printf("%s\nSOMA: %i\n", solucao[melhorSol].stringSolucao, solucao[melhorSol].soma);
        printf("--------------------\n");
    }else
        printf("Nao existe solucao!\n");
    system(EXIT_SUCCESS);
}

void execGulosa(int atual, int valSolucao, char solucaoVertice[]){
    int x;
    int menorPos, menorVal=0;
    int statusInicial = 0;      // zero indica que é a primeira vez que está passando
    int status;
    int statusSolucao=0;
    char valor[10];
    for(x=0;x<j;x++){
        if(atual != x){
            if(matriz[atual][x] != 0){
                if(statusInicial == 0){     // mostra que é para colocar o primeiro elemento possível (verificado) nas variáveis
                    status = verificaSolucao(x);
                    if(status == 1){    // se o elemento estiver inviável, só passa adiante
                        menorVal = matriz[atual][x];
                        menorPos = x;
                        //status = 0;
                        statusInicial = 1;
                        statusSolucao = 1;
                    }
                }else{
                    if(matriz[atual][x] < menorVal){
                        status = verificaSolucao(x);
                        if(status == 1){
                            menorVal = matriz[atual][x];
                            menorPos = x;
                        }
                    }
                }
            }
        }
    }
    soma = soma + menorVal;
    vetVerifica[menorPos] = 1;
    sprintf(valor, "%i", menorPos);
    strcat(solucaoVertice, valor);
    strcat(solucaoVertice, " ");
    //solucao[valSolucao].soma = soma;
            // PROBLEMA, VER COMMIT
    if(statusSolucao == 1){       // encontrou uma solucao viável para o vertice atual
        printf(" %i", menorPos);
        if(verificaFinal() == 0)  // nao acabou
            execGulosa(menorPos, valSolucao, solucaoVertice);
        else{       // acabou e salva a solucao
            if(nSolucoes == 0)
                solucao = (struct _solucao*)malloc(sizeof(struct _solucao)*(nSolucoes+1));
            else
                solucao = realloc(solucao, sizeof(struct _solucao)*(nSolucoes+1));
            solucao[nSolucoes].stringSolucao = malloc(sizeof(char)*i*4);
            strcpy(solucao[nSolucoes].stringSolucao, solucaoVertice);
            solucao[nSolucoes].soma = soma;
            nSolucoes++;
            printf("\tSOLUCAO!");
        }
    }else
        printf("\tsem solução!");
}

int verificaSolucao(int prox){
    if(vetVerifica[prox] == 0)
        return 1;   // não foi acessado ainda, pode ser solução
    else
        return 0;   // já foi acessado, não é viável para solução
}


void zerarVet(){
    int x;
    printf("Entrou zerar");
    for(x=0; x<i; x++)
        vetVerifica[x] = 0;
    soma = 0;
}

int verificaFinal(){
    int x, status=1;
    for(x=0;x<i;x++)
        if(vetVerifica[x] == 0)   // nao finalizou
            status = 0;
    return status;
}

int verifMelhorSolucao(){
    int mSoma, mPos, init=0;
    int x;
    for(x=0; x<nSolucoes; x++){
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


void mostrarSolucoes(){
    int x;
    for(x=0; x<nSolucoes; x++)
        printf("SOLUCAO [%i]: %s\tSOMA: %i\n", x, solucao[x].stringSolucao, solucao[x].soma);
}
