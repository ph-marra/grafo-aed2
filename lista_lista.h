#ifndef _LISTA_LISTA_H
#define _LISTA_LISTA_H
#endif

#ifndef _LISTA_H
#define _LISTA_H
#include "lista.h"
#endif

struct NoLista{
    Lista no;
    struct NoLista* prox;
};
typedef struct NoLista* ListaLista;

ListaLista IniciaListaLista(void);
int VaziaListaLista(ListaLista ll);
int InsereLista(ListaLista *ll, Lista l);
int EsvaziaListaLista(ListaLista *ll);