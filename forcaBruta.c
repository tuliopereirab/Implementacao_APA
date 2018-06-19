#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct verif{
    int val;
    struct verif *prox;
};


// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();
//INTERNAS
int verifica(struct verif *pilha, int val);
void busca(int val, struct verif *pilha, int soma, struct verif *aux, int visitados[], int contador);

//GLOBAIS
int **matriz;
int i, j;



void forcaBruta(char arquivo[]){
    int x, y;
    int *visitados;
    visitados = malloc(sizeof(int)*i);
    struct verif *pilha = NULL;
    struct verif *aux;
    matriz = lerArquivo(arquivo);
    i = retI();
    j = retJ();

    printf("Iniciando solução 'Força Bruta'\n");

    /*for(x=0; x<i; x++){
        if(pilha == NULL){
            pilha = (struct verif*)malloc(sizeof(struct verif));
            pilha->prox = NULL;
            pilha->val = x;
            aux = pilha;
        }
        printf("%i ", x);
        busca(x, pilha, 0, aux, visitados, 0);
        free(pilha);
    }
*/
    system(EXIT_SUCCESS);
}

void busca(int val, struct verif *pilha, int soma, struct verif *aux, int visitados[], int contador){
    int x,y;
    int status;
    for(x=0;x<j;x++){
        if(x!=val){
            status = verifica(pilha, x);
            if(status == 0){     // não está na pilha
                aux->prox = (struct verif*)malloc(sizeof(struct verif));
                aux = aux->prox;
                aux->val = x;
                aux->prox = NULL;
                soma = soma + matriz[val][x];
                busca(x, pilha, soma, aux, visitados, contador+1);
                break;
            }
        }
        printf("%i ", visitados[x]);
    }
}

int verifica(struct verif *pilha, int val){
    int i;
    struct verif *aux = pilha;
    while(aux != NULL){
        if(aux->val == val){
            //printf("Não esta!\n");
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}
