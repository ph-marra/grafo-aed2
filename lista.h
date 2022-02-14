#ifndef _LISTA_H
#define _LISTA_H
#endif

#ifndef _NO_H
#define _NO_H
#include "no.h"
#endif

#ifndef _VERTICE_H
#define _VERTICE_H
#include "vertice.h"
#endif

typedef struct No* Lista;

Lista IniciaLista(void);
int VaziaLista(Lista l);
int Insere(Lista *l, Vertice v);
int Remove(Lista *l, Vertice v);
int EsvaziaLista(Lista *l);