#ifndef _PILHA_H
#define _PILHA_H
#endif

#ifndef _NO_H
#define _NO_H
#include "no.h"
#endif

#ifndef _VERTICE_H
#define _VERTICE_H
#include "vertice.h"
#endif

typedef struct No* Pilha;

Pilha IniciaPilha(void);
int VaziaPilha(Pilha p);
int Topo(Pilha p, Vertice v);
int Empilha(Pilha *p, Vertice v);
int Desempilha(Pilha *p, Vertice v);
int EsvaziaPilha(Pilha *p);