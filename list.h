#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/*
    Estrutura lista simples.
*/

typedef struct _List List;
typedef struct _Node Node;

struct _Node {
    Node *next;
    Node *prev;
    void *value;
};

struct _List {
    Node *root;
    Node *last;
};

// Fun��es de aux�lio para converter int to void* e vice-versa.
void *intToVoid(int value);

// Cria uma nova lista.
List *listCreate();

// Clona a estrutura com os dados de uma lista de inteiros "source".
List *listCloneInt(List *source);

// Insere um valor na lista.
void listInsert(List *list, void *value);

// Pega um elemento da lista pelo �ndice, retorna null se o �ndice n�o existe.
void *listGet(List *list, int index);

// Encontra um elemento do tipo int na lista, retornando seu �ndice ou -1 se n�o achou.
int listFindInt(List *list, int value);

// Limpa a lista.
void listClear(List *list);

// Libera a lista com todos os seus valores.
void listDestroy(List *list);

// 1 se a lista est� vazia ou n�o existe, 0 caso contratio.
int listIsEmpty(List *list);

#endif // LIST_H_INCLUDED
