#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _solucaoForca{
    char *stringSol;
    int soma;
};

// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
//---------------------------
// LOCAIS
void forcaBruta(char arquivo[]);
void execForca(int vetVerifica[]);
void recForca(int atual, int vetVerifica[], char solucaoIntern[], int soma);
int verFinal(int vetVerifica[]);
int verificar(int vetVerifica[], int prox, int atual);
int* zerar(int vetVerifica[]);
void salvarSolucao(char solucaoIntern[], int soma);
//---------------------------
// GLOBAIS
int i, j;
int **matriz;
struct _solucaoForca *solucaoForca = NULL;
int numSolucoes = 0;

void forcaBruta(char arquivo[]){
    int *vetVerifica;

    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();
    vetVerifica = malloc(sizeof(int)*i);
    vetVerifica = zerar(vetVerifica);

    execForca(vetVerifica);


    system(EXIT_SUCCESS);
}

void execForca(int vetVerifica[]){
    int x=0;
    char val[10];
    char *solucaoIntern;
    solucaoIntern = (char*)malloc(sizeof(char)*4*i);
    for(x=0; x<i; x++){
        sprintf(val, "%i", x);
        printf("Teste: %i %i %s\n", i, x, val);
        //printf("Primeiro valor: %i ", x);
        strcpy(solucaoIntern, val);
        strcat(solucaoIntern, " ");
        recForca(x, vetVerifica, solucaoIntern, 0);
    }
    printf("Numero de soluções: %i\n", numSolucoes);
    system(EXIT_SUCCESS);
}

void recForca(int atual, int vetVerifica[], char solucaoIntern[], int soma){
    int x, tam;
    //char *solInt;
    char valor[10];
    tam = strlen(solucaoIntern);
    //solInt = malloc(sizeof(char)*tam);
    //strcpy(solInt, solucaoIntern);
    for(x=0;x<i;x++){
        if(verFinal(vetVerifica) == 0){           // ainda não terminou
            if(verificar(vetVerifica, x, atual) == 0){       // vertice x aceito para ser o proximo
                printf("%i ", x);
                vetVerifica[x] = 1;          // salva que o vertice x já foi acessado
                sprintf(valor, "%i", x);        //
                strcat(solucaoIntern, valor);
                strcat(solucaoIntern, " ");
                soma = soma + matriz[atual][x];
                recForca(x, vetVerifica, solucaoIntern, soma);
            }
        }else{
            salvarSolucao(solucaoIntern, soma);
            numSolucoes++;
            x = i;
        }
    }
}

int verFinal(int vetVerifica[]){
    int x, fim = 1;
    for(x=0;x<i;x++)
        if(vetVerifica[x] == 0)
            fim = 0;    // nem todos os vértices foram acessados
    return fim;

}

int verificar(int vetVerifica[], int prox, int atual){
    if(vetVerifica[prox] == 1)
        return 1;    // já foi acessado
    else
        if(matriz[atual][prox] != 0)
            return 0;       // retorna que o proximo vértice é viável
        else
            return 1;       // retorna que não existe ligação entre os dois vértices
}

int* zerar(int vetVerifica[]){
    int x;
    for(x=0;x<i;x++)
        vetVerifica[x] = 0;
    return vetVerifica;
}

void salvarSolucao(char solucaoIntern[], int soma){
    int tam;
    tam = strlen(solucaoIntern);
    if(numSolucoes == 0){
        solucaoForca =(struct _solucaoForca*)malloc(sizeof(struct _solucaoForca));
    }else
        solucaoForca =realloc(solucaoForca, sizeof(struct _solucaoForca)*numSolucoes+1);
    solucaoForca[numSolucoes].stringSol = malloc(sizeof(char)*tam);
    strcpy(solucaoForca[numSolucoes].stringSol, solucaoIntern);
    solucaoForca[numSolucoes].soma = soma;
}
