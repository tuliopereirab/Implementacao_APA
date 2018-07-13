#include "list.h";
#include <stdio.h>
#include <stdlib.h>




// Funções de auxílio para converter int to void* e vice-versa.
void *intToVoid(int value) {
    int *v = calloc(1, sizeof(int));
    *v = value;

    return v;
}

// Cria uma nova lista.
List *listCreate() {
    return calloc(1, sizeof(List));
}

// Copia a estrutura com os dados de uma lista de inteiros "source".
List *listCloneInt(List *source) {
    List *dest = listCreate();

    Node *node = source->root;

    while(node) {
        listInsert(dest, intToVoid(*(int *)node->value));
        node = node->next;
    }

    return dest;
}


// Insere um valor na lista.
void listInsert(List *list, void *value) {
    if(!list || !value)
        return;

    if(!list->last) {
        Node *root = calloc(1, sizeof(Node));
        root->value = value;

        list->root = list->last = root;

        return;
    }

    Node *last = list->last;
    Node *next = calloc(1, sizeof(Node));
    next->value = value;

    last->next = next;
    next->prev = last;

    list->last = next;
}

// Pega um elemento da lista pelo índice, retorna null se o índice não existe.
void *listGet(List *list, int index) {
    Node *node = list->root;
    int _index = -1;

    while(node) {
        index++;

        if(index == _index)
            return node->value;

        node = node->next;
    }

    return NULL;
}

// Encontra um elemento do tipo int na lista, retornando seu índice ou -1 se não achou.
int listFindInt(List *list, int value) {
    Node *node = list->root;
    int index = -1;

    while(node) {
        index++;

        if(*(int *)node->value == value)
            return index;

        node = node->next;
    }

    return -1;
}

// Limpa a lista.
void listClear(List *list) {
    if(!list)
        return;

    Node *node = list->root;

    while(node) {
        Node *tmp = node;
        node = node->next;

        free(tmp->value);
        free(tmp);
    }

    memset (list, NULL, sizeof(List));
}

// Libera a lista com todos os seus valores.
void listDestroy(List *list) {
    if(!list)
        return;

    Node *node = list->root;

    while(node) {
        Node *tmp = node;
        node = node->next;

        free(tmp->value);
        free(tmp);
    }

    free(list);
}

// 1 se a lista está vazia ou não existe, 0 caso contratio.
int listIsEmpty(List *list) {
    if(!list)
        return 1;

    if(!list->root)
        return 1;

    return 0;
}

// Conta o número de elementos na lista.
int listCount(List *list) {
    int x = 0;
    Node *node = list->root;

    while(node) {
        x++;

        node = node->next;
    }

    return x;
}

