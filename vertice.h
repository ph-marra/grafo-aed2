#ifndef _VERTICE_H
#define _VERTICE_H
#endif

#ifndef MAX
#define MAX 100
#endif

struct vertice{
   char nome[MAX];
   int tipo;
   int acao;
};
typedef struct vertice* Vertice;

int iguaisVertices(Vertice v1, Vertice v2);