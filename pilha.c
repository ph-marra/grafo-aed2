#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha IniciaPilha(void){
   return NULL;
}

int VaziaPilha(Pilha p){
   return (p == NULL);
}

int Topo(Pilha p, Vertice v){
   if(VaziaPilha(p))
      return 0;

   *v = p->vert;
   return 1;
}


int Empilha(Pilha *p, Vertice v){
   if(p == NULL || v == NULL)
      return 0;

   struct No* no = (struct No*)malloc(sizeof(struct No));
   if(no == NULL)
      return 0;

   no->vert = *v;
   no->prox = *p;
   *p = no;
   return 1;
}

int Desempilha(Pilha *p, Vertice v){
   if(p == NULL || v == NULL || VaziaPilha(*p))
      return 0;

   struct No* aux = *p;
   *v = aux->vert;
   *p = aux->prox;
   free(aux);

   return 1;
}

int EsvaziaPilha(Pilha *p){
   if(p == NULL)
      return 0;

   if(VaziaPilha(*p))
      return 1;

   struct No* aux = *p;

   while(aux != NULL){
      *p = aux;
      aux = aux->prox;
      free(*p);
   }

   *p = NULL;
   return 1;
}