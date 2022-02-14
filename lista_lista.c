#include <stdio.h>
#include <stdlib.h>
#include "lista_lista.h"

ListaLista IniciaListaLista(void){
    return NULL;
}

int VaziaListaLista(ListaLista ll){
    return (ll == NULL);
}

int InsereLista(ListaLista *ll, Lista l){
    if(ll == NULL)
        return 0;

    struct NoLista* fst = (struct NoLista*)malloc(sizeof(struct NoLista));
    if(fst == NULL)
        return 0;

    fst->no = l;
    fst->prox = *ll;
    *ll = fst;

    return 1;
}


int EsvaziaListaLista(ListaLista *ll){
    if(ll == NULL)
        return 0;

    if(VaziaListaLista(*ll))
        return 1;

    struct NoLista* aux = *ll;

    while(aux != NULL){
        *ll = aux;
        aux = aux->prox;
        EsvaziaLista(&(*ll)->no);
        free(*ll);
    }

    *ll = NULL;
    return 1;
}