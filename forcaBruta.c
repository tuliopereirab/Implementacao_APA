#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// EXTERNAS
int **lerArquivo(char arquivo[]);
int retI();
int retJ();

//INTERNAS
void forcaBrutaBusca(int verticeAtual, List *caminhoAteAgora, List *custoAteAgora);
int aviso();

//GLOBAIS
int **Matriz;
int I, J, VerticeDestino;
List *MelhorCaminho, *Caminhos, *CaminhosCusto;
int MelhorCaminhoCusto = -1;

/*
    Obs: Considerei o vértice inicial o 0 e o final o J - 1, mas seria interessante colocar essas entradas como parâmetro.
    Também criei uma estrutura de lista para auxiliar nesse algoritmo.
*/
void forcaBruta(char arquivo[]){
    Matriz = lerArquivo(arquivo);
    int h;
    int statusAviso;
    I = retI();
    J = retJ();

    printf("Iniciando solucao \"Forca Bruta\" | matriz: %d x %d | vertice inicial: %d | vertice final: %d.\n\n", I, J, 0, J - 1);

    if(I > 13) statusAviso = aviso();
    else statusAviso = 0;   // indica que pode continuar executando sem problemas

    if(statusAviso == 1){
        printf("Finalizando...\n");
        system(EXIT_SUCCESS);
    }

    printf("Iniciando execução...");

    List *caminhoAteAgora = listCreate();
    List *custoAteAgora = listCreate();
    Caminhos = listCreate();
    CaminhosCusto = listCreate();

    listInsert(caminhoAteAgora, intToVoid(0));
    listInsert(custoAteAgora, intToVoid(0));

    VerticeDestino = J - 1;

    forcaBrutaBusca(0, caminhoAteAgora, custoAteAgora);

    if(listIsEmpty(Caminhos)) {
        puts("Não foi encontrado nenhum caminho.");
    } else {
        // Imprimi todos os caminhos possíveis guardados na lista "Caminhos".
        puts("Caminhos encontrados:\n");

        Node *no = Caminhos->root;
        Node *noCusto = CaminhosCusto->root;
        while(no) {
            List *caminho = no->value;
            Node *vertice = caminho->root;

            while(vertice) {
                printf("> %d ", *(int *)vertice->value);
                vertice = vertice->next;
            }

            printf(" | custo = %d.\n", *(int *)noCusto->value);

            no = no->next;
            noCusto = noCusto->next;
            listDestroy(caminho);
        }

        // Imprimi o melhor caminho.
        printf("\nMelhor caminho | custo = %d:\n\n", MelhorCaminhoCusto);

        no = MelhorCaminho->root;
        while(no) {
            printf("> %d ", *(int *)no->value);
            no = no->next;
        }
    }

    // Libera memória.
    listDestroy(Caminhos);
    listDestroy(MelhorCaminho);
    listDestroy(CaminhosCusto);

    int x = 0;
    for(x = 0; x < I; x++) {
        free(Matriz[x]);
    }
    free(Matriz);

    puts("\n\nFinalizado.");

    system(EXIT_SUCCESS);
}

/*
    Retorna o custo total de um caminho.
*/
int obterCustoCaminho(List *list) {
    Node *node = list->root;

    int size = 0;
    while(node) {
        size += *(int *)node->value;
        node = node->next;
    }

    return size;
}

/*
    Executa uma busca em largura no grafo.

    caminhoAteAgora: mantém os vértices do caminho percorrido, isso é necessário para que a partir do momento
    que visitou um vértice x, nunca mais volte para esse vértice x.
    custoAteAgora: mantém o custo do caminho percorrido.
*/
void forcaBrutaBusca(int verticeAtual, List *caminhoAteAgora, List *custoAteAgora) {

    // "&& listCount(caminhoAteAgora) == J" -> Caixeiro viajante tem que passar por todos os vértices
    // para o caminho ser aceito.
    if(verticeAtual == VerticeDestino && listCount(caminhoAteAgora) == J) {
        // Adiciona caminho na lista que guarda os caminhos possíveis.
        listInsert(Caminhos, listCloneInt(caminhoAteAgora));

        int caminhoCusto = obterCustoCaminho(custoAteAgora);

        listInsert(CaminhosCusto, intToVoid(caminhoCusto));

        if(caminhoCusto < MelhorCaminhoCusto || MelhorCaminhoCusto == -1) {
            // Encontrou um novo caminho ótimo.
            MelhorCaminhoCusto = obterCustoCaminho(custoAteAgora);

            listDestroy(MelhorCaminho);
            MelhorCaminho = listCloneInt(caminhoAteAgora);
        }
    } else {
        int x = 0;
        for(x = 0; x < J; x++) {
            // Só irá visitar o vértice se esse vértice ainda não foi visitado e se o custo até ele é > 0.
            // Vértice com custo = 0 é considerado sem aresta de ligação.
            if(listFindInt(caminhoAteAgora, x) == -1) {
                if(Matriz[verticeAtual][x] > 0) {

                    List *novoCaminhoAteAgora = listCloneInt(caminhoAteAgora);
                    List *novocustoAteAgora = listCloneInt (custoAteAgora);

                    listInsert(novoCaminhoAteAgora, intToVoid(x));
                    listInsert(novocustoAteAgora, intToVoid(Matriz[verticeAtual][x]));

                    forcaBrutaBusca(x, novoCaminhoAteAgora, novocustoAteAgora);
                }
            }
        }
    }

    listDestroy(caminhoAteAgora);
    listDestroy(custoAteAgora);
}

int aviso(){
    int x, status;
    char c;
    printf("\n--------------------- AVISO---------------------\n");
    printf("Você está tentando executar a solução de uma matriz %ix%i por FORÇA BRUTA!\n", I, I);
    printf("Uma matriz de tal normalmente trava os computadores.\n");
    printf("Por favor, confirme se quer continuar a execução [y/n] -> ");
    scanf("%c", &c);
    while(c != 'y' && c != 'n'){
        printf("\nErro! Digite 'y' para sim ou 'n' para não.\n");
        printf("Por favor, confirme se quer continuar a execução [y/n] -> ");
        scanf("%c", &c);
    }
    if(c == 'n') return 1;
    else return 0;
}
