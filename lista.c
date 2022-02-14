#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista IniciaLista(void){
    return NULL;
}

int VaziaLista(Lista l){
    return (l == NULL);
}

int Insere(Lista *l, Vertice v){
    if(l == NULL || v == NULL)
        return 0;

    struct No* no = (struct No*)malloc(sizeof(struct No));
    if(no == NULL)
        return 0;

    no->vert = *v;
    no->prox = *l;
    *l = no;
    return 1;
}

int Remove(Lista *l, Vertice v){
    if(l == NULL || v == NULL || VaziaLista(*l))
      return 0;

    struct No* aux = *l, *remover;

    if(iguaisVertices(&aux->vert, v)){ // 1o e com 1 soh elemento
        *l = aux->prox;
        free(aux);
        return 1;
    }

    for(aux; aux->prox != NULL && !iguaisVertices(&aux->prox->vert, v); aux = aux->prox);

    if(aux->prox == NULL) return 0;

    remover = aux->prox;
    aux->prox = remover->prox;
    free(remover);
    return 1;  
}

int EsvaziaLista(Lista *l){
    if(l == NULL)
        return 0;

    if(VaziaLista(*l))
        return 1;

    struct No* aux = *l;

    while(aux != NULL){
        *l = aux;
        aux = aux->prox;
        free(*l);
    }

    *l = NULL;
    return 1;
}