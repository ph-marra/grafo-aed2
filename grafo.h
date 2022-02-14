#ifndef _GRAFO_H
#define _GRAFO_H
#endif

#ifndef _PILHA_H
#define _PILHA_H
#include "pilha.h"
#endif

#ifndef _LISTA_LISTA_H
#define _LISTA_LISTA_H
#include "lista_lista.h"
#endif

#ifndef _VERTICE_H
#define _VERTICE_H
#include "vertice.h"
#endif

/*
Tipo: (1) Arquivo - (2) Página (3) - Pasta - (4) Tarefa - (5) URL
Ação: (1) Download - (2) Upload - (3) Visualizar
*/

struct noAdj { 
   struct vertice vert;
   int peso; 
   struct noAdj *prox; 
};
typedef struct noAdj* ListaAdjacencia;

struct noVert { 
   struct vertice vert;
   struct noAdj *ladj; 
   struct noVert *prox;
};
typedef struct noVert* ListaVertices;

struct grafo {
   int NumVert; 
   int NumArco; 
   ListaVertices vertices; 
};
typedef struct grafo* Grafo;

struct visitaTempo{
   struct vertice vert;
   int tempoDescoberta;
   int tempoFinalizacao;
};
typedef struct visitaTempo* Tempo;

struct distancia{
   struct vertice vert;
   int distancia;
};
typedef struct distancia* Distancia;

Grafo criarGrafoNulo(void);
int EhNulo(Grafo G);
Grafo criarGrafoVazio(Vertice* lv, int t);
int EsvaziaGrafo(Grafo G);
int AnulaGrafo(Grafo G);
int ApagaGrafo(Grafo* G);
int inserirArco(Grafo G, Vertice v1, Vertice v2, int peso);
int inserirVertice(Grafo G, Vertice v);
int removerArco(Grafo G, Vertice v1, Vertice v2);
int removerVertice(Grafo G, Vertice v);
int CopiaGrafo(Grafo G, Grafo* H);
int grauVertice(Grafo G, Vertice v, int* grau);
int maiorGrau(Grafo G, Vertice v, int *gm);
int BuscaEmProfundidade(Grafo G, Vertice v, Vertice* lv, int* t);
int BuscaEmProfundidadeTempo(Grafo G, Vertice v, Tempo* lv, int* t);
int existeCaminho(Grafo G, Vertice v1, Vertice v2);
int Transposto(Grafo G, Grafo* H);
int BuscaTodosTempo(Grafo G, Tempo* lv);
int Kosaraju(Grafo G, ListaLista* rfc);
int Dijkstra(Grafo G, Vertice v, Distancia* ld);