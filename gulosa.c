#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _solucao{
    char *stringSolucao;
    int soma;
};

// INTERNAS
void execGulosa(int atual, int vetVerifica[], int valSolucao, char solucaoVertice[]);
int verificaSolucao(int vetVerifica[], int prox);
int* zerarVet(int vetVerifica[]);
int verificaFinal(int vetVerifica[]);
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



void gulosa(char arquivo[]){
    int x, y;

    int *vetVerifica;
    char valor[10];
    int melhorSol;
    char *solucaoVertice;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    solucaoVertice = malloc(sizeof(char)*4*i);
    vetVerifica = malloc(sizeof(int)*i);
    printf("Encontrando soluções...\n");
    printf("------------------------------------\n");

    for(x=0; x<i; x++){     // irá chamar execGulosa n vezes (sendo n o numero de vertices) - isso indica que vai ser tentado encontrar um caminho partindo de cada uma das soluções
        vetVerifica = zerarVet(vetVerifica);
        printf("Solução partindo de %i: %i", x, x);
        sprintf(valor, "%i", x);
        strcpy(solucaoVertice, valor);
        strcat(solucaoVertice, " ");
        vetVerifica[x] = 1;
        execGulosa(x, vetVerifica, x, solucaoVertice);
        printf("\n");
    }
    printf("------------------------------------\n");
    printf("Numero de soluções: %i\n", nSolucoes);
    if(nSolucoes != 0){
        melhorSol = verifMelhorSolucao();     // receberá a posição no vetor da melhor solução
        mostrarSolucoes();      // mostra todas as soluções encontradas
        printf("--------------------\n");
        printf("MELHOR SOLUCAO: \n");
        printf("%s\nSOMA: %i\n", solucao[melhorSol].stringSolucao, solucao[melhorSol].soma);
        printf("--------------------\n");
    }else
        printf("Nao existe solucao!\n");
    system(EXIT_SUCCESS);
}

void execGulosa(int atual, int vetVerifica[], int valSolucao, char solucaoVertice[]){
    int x;
    int menorPos, menorVal=0;
    int statusInicial = 0;      // zero indica que é a primeira vez que está passando
    int status;
    int statusSolucao=0;
    char valor[10];
    for(x=0;x<j;x++){
        if(atual != x){
            if(matriz[atual][x] != 0){     // caso seja verdade, indica que existe uma ligação entre o vertice atual e o vertice X
                if(statusInicial == 0){     // mostra que é para colocar o primeiro elemento possível (verificado) nas variáveis
                    status = verificaSolucao(vetVerifica, x);
                    if(status == 1){    // se o elemento estiver inviável, só passa adiante
                        menorVal = matriz[atual][x];
                        menorPos = x;
                        statusInicial = 1;
                        statusSolucao = 1;
                    }
                }else{       // indica que não está mais em estado inicial e que as variáveis menorVal e menorPos já possuem um valor para serem comparadas
                    if(matriz[atual][x] < menorVal){
                        status = verificaSolucao(vetVerifica, x);
                        if(status == 1){         // verifica que a solução X para o vertice atual é aceita (X ainda não foi acessado)
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
    if(statusSolucao == 1){       // encontrou uma solucao viável para o vertice atual
        printf(" %i", menorPos);
        if(verificaFinal(vetVerifica) == 0)  // nao acabou (ainda existem vértices que não foram acessados)
            execGulosa(menorPos, vetVerifica, valSolucao, solucaoVertice);
        else{       // acabou e salva a solucao
            if(nSolucoes == 0)       // se for a primeira solução, aloca a solução
                solucao = (struct _solucao*)malloc(sizeof(struct _solucao)*(nSolucoes+1));
            else    // se nao for a primeira, apenas aumenta o vetor de soluções em uma posição
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

int verificaSolucao(int vetVerifica[], int prox){
    if(vetVerifica[prox] == 0)
        return 1;   // não foi acessado ainda, pode ser solução
    else
        return 0;   // já foi acessado, não é viável para solução
}


int* zerarVet(int vetVerifica[]){
    int x;
    for(x=0; x<i; x++)
        vetVerifica[x] = 0;
    soma = 0;
    return vetVerifica;
}

int verificaFinal(int vetVerifica[]){
    int x, status=1;
    for(x=0;x<i;x++)
        if(vetVerifica[x] == 0)   // nao finalizou
            status = 0;      // uma vez que status virou zero, indica que não terminou e esse será o valor retornado
    return status;
}

int verifMelhorSolucao(){         // encontra a solução com valor de soma mais baixo e retorna posição
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
