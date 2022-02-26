#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#ifndef TRUE
#define TRUE 1
#endif

struct auxDijkstra{
   struct distancia info;
   char visitado;
};
typedef struct auxDijkstra* Dijk;


Grafo criarGrafoNulo(void){
   Grafo g = (Grafo) malloc(sizeof(struct grafo));
   if(g == NULL) return g;
   g->NumVert = 0;
   g->NumArco = 0;
   g->vertices = NULL;

   return g;
}

int EhNulo(Grafo G){
   if(G == NULL) return 0;
   return (G->vertices == NULL);
}

Grafo criarGrafoVazio(Vertice* lv, int t) {
   Grafo g = criarGrafoNulo();
   if(g == NULL) return NULL;

   for(int i = 0; i < t; i++)
      if(!inserirVertice(g, &(*lv)[i])){
         AnulaGrafo(g);
         free(g);
         return NULL;
      }

   return g;   
}

int EsvaziaGrafo(Grafo G){
   if(G == NULL)
      return 0;

   struct noVert* v;
   struct noAdj* a;

   for(v = G->vertices; v != NULL; v = v->prox)
      for(a = v->ladj; a != NULL; a = v->ladj){
         v->ladj = a->prox;
         free(a);
      }
   
   G->NumArco = 0;
   return 1;
}

int AnulaGrafo(Grafo G){
   if(G == NULL)
      return 0;

   struct noVert* v, aux;
   struct noAdj* a;

   for(v = G->vertices; G->vertices != NULL; v = G->vertices){
      for(a = v->ladj; a != NULL; a = v->ladj){
         v->ladj = a->prox;
         free(a);
      }
      G->vertices = v->prox;
      free(v);
   }

   G->NumVert = 0;
   G->NumArco = 0;
   return 1;
}

int ApagaGrafo(Grafo* G){
   if(G == NULL || *G == NULL)
      return 0;
   
   AnulaGrafo(*G);
   free(*G);
   *G = NULL;
   
   return 1;
}

int inserirVertice(Grafo G, Vertice v){
   if(G == NULL)
      return 0;

   struct noVert* aux;

   for(aux = G->vertices; aux != NULL; aux = aux->prox)
      if(iguaisVertices(&aux->vert, v))
         return 0;

   struct noVert* novoVertice = (struct noVert*) malloc (sizeof(struct noVert));
   if(novoVertice == NULL)
      return 0;

   novoVertice->prox = G->vertices;
   G->vertices = novoVertice;
   novoVertice->vert = *v;
   novoVertice->ladj = NULL;
   G->NumVert++;
   return 1;
}

int inserirArco(Grafo G, Vertice v1, Vertice v2, int peso){
   if(G == NULL || v1 == NULL || v2 == NULL)
      return 0;

   struct noVert* v, *vv;
   struct noAdj* a;
   ListaAdjacencia noAdj;

   for(v = G->vertices; v != NULL; v = v->prox)
      if(iguaisVertices(&v->vert, v1)){
         for(vv = G->vertices; vv != NULL && !iguaisVertices(&vv->vert, v2); vv = vv->prox);
            if(vv == NULL) return 0;

         for(a = v->ladj; a != NULL; a = a->prox)
            if(iguaisVertices(&a->vert, v2)) return 0;
            
            noAdj = (ListaAdjacencia) malloc(sizeof(struct noAdj));
            if(noAdj == NULL) return 0;
            
            noAdj->prox = v->ladj;
            v->ladj = noAdj;
            noAdj->peso = peso;
            noAdj->vert = *v2;
            G->NumArco++;

            return 1;
      }
   return 0;
}

int removerArco(Grafo G, Vertice v1, Vertice v2){
   if(G == NULL || v1 == NULL || v2 == NULL)
      return 0;

   struct noVert* v;
   struct noAdj *a, *b;

   for(v = G->vertices; v != NULL; v = v->prox)
      if(iguaisVertices(&v->vert, v1)){
         if(iguaisVertices(&v->ladj->vert, v2)){ // primeiro igual
            a = v->ladj;
            v->ladj = a->prox;
            free(a);
            G->NumArco--;
            return 1;
         }

         for(a = v->ladj; a->prox != NULL; a = a->prox)
            if(iguaisVertices(&a->prox->vert, v2)){
               b = a->prox;
               a->prox = b->prox;
               free(b);
               G->NumArco--;
               return 1;
            }

         return 0;
      }

   return 0;
}

int removerVertice(Grafo G, Vertice v){
   if(G == NULL || v == NULL || G->vertices == NULL)
      return 0;

   int achou = 0;
   struct noVert *aux, *aux1;
   struct noAdj *aux2, *aux3;

   aux = G->vertices;
   while(aux->prox != NULL){
      if(iguaisVertices(&aux->prox->vert, v)){
         aux1 = aux->prox; // v para remover
         while(aux1->ladj != NULL){ // apagando ladj de v
            aux2 = aux1->ladj;
            aux1->ladj = aux2->prox;
            free(aux2);
            G->NumArco--;
         }
         aux->prox = aux1->prox;
         free(aux1);
         G->NumVert--;
      }
      else
         aux = aux->prox;
   }

   if(iguaisVertices(&G->vertices->vert, v)){ // tirar primeiro v de vs
      aux = G->vertices;
      G->vertices = aux->prox;
      while(aux->ladj != NULL){ // apagando ladj de v
         aux2 = aux->ladj;
         aux->ladj = aux2->prox;
         free(aux2);
         G->NumArco--;
      }

      free(aux);
      G->NumVert--;
   }

   for(aux = G->vertices; aux != NULL; aux = aux->prox){
      if(aux->ladj == NULL) continue;
      
      aux2 = aux->ladj;
      while(aux2->prox != NULL){
         if(iguaisVertices(&aux2->prox->vert, v)){
            aux3 = aux2->prox;
            aux2->prox = aux3->prox;
            free(aux3);
            G->NumArco--;
         }
         else
            aux2 = aux2->prox;
      }

      if(iguaisVertices(&aux->ladj->vert, v)){
         aux2 = aux->ladj;
         aux->ladj = aux2->prox;
         free(aux2);
         G->NumArco--;
      }
   }

   return 1;
}

int CopiaGrafo(Grafo G, Grafo* H){
   if(G == NULL || H == NULL)
      return 0;
        
    *H = criarGrafoNulo();
    if(*H == NULL) return 0;

   struct noVert* v;
   struct noAdj* a;

   for(v = G->vertices; v != NULL; v = v->prox)
      if(!inserirVertice(*H, &v->vert)){
         ApagaGrafo(H);
         return 0;
      }

   for(v = G->vertices; v != NULL; v = v->prox)
      for(a = v->ladj; a != NULL; a = a->prox)
         if(!inserirArco(*H, &v->vert, &a->vert, a->peso)){
            ApagaGrafo(H);
            return 0;
         }

   return 1;
}

int grauVertice(Grafo G, Vertice v, int* grau){
   if(G == NULL || v == NULL)
      return 0;

   struct noVert* aux;
   struct noAdj* aux1;
   int cont = 0, existe = 0;

   for (aux = G->vertices; aux != NULL; aux = aux->prox)
      if(iguaisVertices(&aux->vert, v))
         for(aux1 = aux->ladj, existe = 1; aux1 != NULL; aux1 = aux1->prox)
            cont += 1;
      else
         for(aux1 = aux->ladj; aux1 != NULL; aux1 = aux1->prox)
            if(iguaisVertices(&aux1->vert, v))
               cont += 1;

   *grau = cont;
   return existe;
}

int maiorGrau(Grafo G, Vertice v, int *gm){
   if(G == NULL || v == NULL || G->vertices == NULL)
      return 0;

   struct noVert *aux = G->vertices, *maior;
   int grauAux = 0;
   grauVertice(G, &aux->vert, &grauAux);

   for(maior = aux, aux = aux->prox, *gm = grauAux; aux != NULL; aux = aux->prox){
      grauVertice(G, &aux->vert, &grauAux);
      if(grauAux > *gm){
         maior = aux;
         *gm = grauAux;
      } 
   }

   *v = maior->vert;
   return 1;
}

int FoiVisitado(Pilha p, Vertice v){
   for(struct No* aux = p; aux != NULL; aux = aux->prox)
      if(iguaisVertices(v, &aux->vert))
         return 1;
   
   return 0;
}

int BuscaEmProfundidade(Grafo G, Vertice v, Vertice* lv, int* t) {
   if(G == NULL || v == NULL || lv == NULL || t == NULL)
      return 0;

   struct noVert *nv;
   for(nv = G->vertices; nv != NULL && !iguaisVertices(&nv->vert, v); nv = nv->prox);
   if(nv == NULL)
      return 0;

   struct noAdj *na;
   int cont = 0;
   Pilha p = IniciaPilha(), visitados = IniciaPilha();
   Vertice vt = (Vertice)malloc(sizeof(struct vertice));
   if(vt == NULL)
      return 0;
   
   if(!Empilha(&p, v)){
      free(vt);
      return 0;
   }
   
   while(!VaziaPilha(p)){
      Desempilha(&p, vt);
      if(!FoiVisitado(visitados, vt)){
         if(!Empilha(&visitados, vt)){
            EsvaziaPilha(&p);
            EsvaziaPilha(&visitados);
            free(vt);
            return 0;
         }
         
         cont++;
         for(nv = G->vertices; nv!=NULL; nv = nv->prox)
            if(iguaisVertices(vt, &nv->vert)){
               for(na = nv->ladj; na != NULL; na = na->prox)
                  if(!FoiVisitado(visitados, &na->vert))
                     if(!Empilha(&p, &na->vert)){
                        EsvaziaPilha(&p);
                        EsvaziaPilha(&visitados);
                        free(vt);
                        return 0;
                     }
               continue;
            }
      }     
   }
   
   *lv = (Vertice)malloc(cont*sizeof(struct vertice));
   if(*lv == NULL){
      EsvaziaPilha(&visitados);
      free(vt);
      return 0;
   }
      
   for(*t = cont; !VaziaPilha(visitados);){
      Desempilha(&visitados, vt);
      (*lv)[--cont] = *vt;
   }

   free(vt);
   return 1;
}

int MarcaVisitaTempo(Vertice vt, int pos, char tipo, Tempo vet, int tam){
   for (int i = 0; i<tam; i++)
      if(iguaisVertices(&vet[i].vert, vt))
         if (tipo == 'D'){
            vet[i].tempoDescoberta = pos;
            return 1;
         }   
         else
               if (vet[i].tempoFinalizacao == -1){
                  vet[i].tempoFinalizacao = pos;
                  return 1;
               }
               else return 0;                

   return 0;
}

int FoiVisitadoTempo(Vertice vt, Tempo vet, int tam){
   for (int i = 0; i<tam; i++)
      if(iguaisVertices(&vet[i].vert, vt) && vet[i].tempoDescoberta != -1)
         return 1;

  return 0;
}

int BuscaEmProfundidadeTempo_(Grafo G, Vertice v, int* cont, Tempo* lv, int* t){
   if(G == NULL || v == NULL || lv == NULL || t == NULL)
      return 0;

   struct noVert* nv;
   struct noAdj* na;
   Tempo visitados;
   Pilha p = IniciaPilha();
   int tam = 0, finaliza, r;
   Vertice vt = (Vertice)malloc(sizeof(struct vertice));
   if(vt == NULL)
      return 0;

   //Iniciar o vetor de visitados com -1 para todos os vértices
   visitados = (Tempo) malloc (G->NumVert * sizeof (struct visitaTempo));
   if(visitados == NULL)
      return 0;
   
   for (nv = G->vertices; nv!=NULL; nv=nv->prox, tam++){
      visitados[tam].vert = nv->vert;
      visitados[tam].tempoDescoberta = -1;
      visitados[tam].tempoFinalizacao = -1;
   }

   if(!Empilha(&p, v)) return 0;
   while(!VaziaPilha(p)){
      Topo(p, vt);
      if (!FoiVisitadoTempo(vt, visitados, tam)){
         MarcaVisitaTempo(vt, (*cont)++, 'D', visitados, tam);
          //cont++;
         for (nv = G->vertices; nv!=NULL; nv = nv->prox) 
            if(iguaisVertices(vt, &nv->vert)){
               finaliza = 1;
               for(na = nv->ladj; na != NULL; na = na->prox)
                  if (!FoiVisitadoTempo(&na->vert, visitados, tam)){
                     if(!Empilha(&p, &na->vert)) return 0;
                     finaliza = 0;
                  }
               if(finaliza == 1){
                  r = MarcaVisitaTempo(vt, *cont, 'F', visitados, tam);
                  if (r == 1) (*cont)++;
                  Desempilha(&p, vt);
               }
            }        
      }
      else{
         r = MarcaVisitaTempo(vt, *cont, 'F', visitados, tam);
         if (r == 1) (*cont)++;
         Desempilha(&p, vt);
      }
   }

   int vis, i;
   for(i = 0, vis = 0; i < tam; i++)
      if(visitados[i].tempoDescoberta != -1)
         vis++;

   *lv = (Tempo)malloc(vis*sizeof(struct visitaTempo));
   *t = vis;

   for(i = 0, vis = 0; i < tam; i++)
      if(visitados[i].tempoDescoberta != -1)
         (*lv)[vis++] = visitados[i]; 
   
   free(visitados);

   return 1;
}

int BuscaEmProfundidadeTempo(Grafo G, Vertice v, Tempo* lv, int* t){
   int c = 1;
   return BuscaEmProfundidadeTempo_(G, v, &c, lv, t);
}

int existeCaminho(Grafo G, Vertice v1, Vertice v2){
   int b1, t1;
   Vertice lv1 = NULL;
   b1 = BuscaEmProfundidade(G, v1, &lv1, &t1);
   if(!b1 || !t1) return 0;

   for(b1 = 0; b1 < t1; b1++)
      if(iguaisVertices(v2, &lv1[b1])){
         free(lv1);
         return 1;
      }

   free(lv1);
   return 0;
}

int Transposto(Grafo G, Grafo* H){
   if(G == NULL || H == NULL)
      return 0;

   *H = criarGrafoNulo();
   if(*H == NULL)
      return 0;

   struct noVert* v1, *v2;
   struct noAdj* a;
   Vertice vs;
   int i;

   for(v1 = G->vertices; v1 != NULL; v1 = v1->prox)
      if(!inserirVertice(*H, &v1->vert)){
         ApagaGrafo(H);
         return 0;
      }

   if(G->NumVert == 0 || G->NumVert == 1)
      return 1;

   for(v1 = G->vertices; v1 != NULL; v1 = v1->prox){
      for(v2 = G->vertices; v2 != NULL; v2 = v2->prox){
         for(a = v1->ladj; a != NULL; a = a->prox)
            if(iguaisVertices(&v2->vert, &a->vert)) // existe v1 -> v2
               if(!inserirArco(*H, &v2->vert, &v1->vert, a->peso)){
                  ApagaGrafo(H);
                  return 0;
               }
      }
   }

   return 1;
}

int BuscaTodosTempo(Grafo G, Tempo* lv){
   if(G == NULL || lv == NULL || !G->NumVert)
      return 0;
 
   Tempo tmps = (Tempo)calloc(G->NumVert, sizeof(struct visitaTempo)), aux = NULL;
   if(tmps == NULL) return 0;

   Grafo GC;
   struct noVert* v;
   Vertice vt;
   int i, j, cont = 1, tamAux;

   if(!CopiaGrafo(G, &GC)){
      free(tmps);
      return 0;
   }

   for(v = GC->vertices, i = 0; v != NULL; v = v->prox, i++){
      tmps[i].vert = v->vert;
      tmps[i].tempoDescoberta = -1;
      tmps[i].tempoFinalizacao = -1;
   }

   while(!EhNulo(GC)){
      vt = &GC->vertices->vert;
      BuscaEmProfundidadeTempo_(GC, vt, &cont, &aux, &tamAux);
      for(i = 0; i < tamAux; i++)
         for(j = 0; j < G->NumVert; j++)
            if(iguaisVertices(&tmps[j].vert, &aux[i].vert) && tmps[j].tempoDescoberta == -1)
               tmps[j] = aux[i];

      for(i = 0; i < tamAux; i++)
         removerVertice(GC, &aux[i].vert);

      free(aux);
      aux = NULL;
   }

   *lv = (Tempo)malloc(G->NumVert*sizeof(struct visitaTempo));
   
   for(i = 0; i < G->NumVert; i++)
      (*lv)[i] = tmps[i];

   free(tmps);
   return 1;

}

int jaVisitado(Pilha visitados, Vertice v){
   for(Pilha aux = visitados; aux != NULL; aux = aux->prox)
      if(iguaisVertices(&aux->vert, v))
         return 1;
   return 0;
}

int Kosaraju(Grafo G, ListaLista* rfc){
   if(G == NULL || rfc == NULL)
      return 0;

   int i, j, menor, tam;
   Tempo lv;
   Grafo GT;
   struct vertice vt;
   Vertice vs;
   Lista compc;

   if(!BuscaTodosTempo(G, &lv)) return 0;

   Pilha p = IniciaPilha(), visitados = IniciaPilha();

   for(i = 0; i < G->NumVert; i++){
      for(j = 0, menor = 0; j < G->NumVert; j++)
         if(lv[j].tempoFinalizacao < lv[menor].tempoFinalizacao)
            menor = j;
      if(!Empilha(&p, &lv[menor].vert)){
         free(lv);
         EsvaziaPilha(&p);
         return 0;
      }
      lv[menor].tempoFinalizacao = INT_MAX;
   }

   free(lv);
   if(!Transposto(G, &GT)) return 0;

   *rfc = IniciaListaLista();

   while(!VaziaPilha(p)){
      Desempilha(&p, &vt);
      if(jaVisitado(visitados, &vt)) continue;
      BuscaEmProfundidade(GT, &vt, &vs, &tam);
      compc = IniciaLista();

      for(i = 0; i < tam; i++)
         if(!jaVisitado(visitados, &vs[i])){
            Empilha(&visitados, &vs[i]);
            Insere(&compc, &vs[i]);
         }
      
      InsereLista(rfc, compc);
   }

   return 1;
}

int Dijkstra(Grafo G, Vertice v, Distancia* ld){
   if(G == NULL || v == NULL || ld == NULL || G->vertices == NULL) return 0;

   struct noVert* vs;
   for(vs = G->vertices; vs != NULL && !iguaisVertices(&vs->vert, v); vs = vs->prox);
   if(vs == NULL) return 0;

   Dijk d = (Dijk)malloc((G->NumVert - 1)*sizeof(struct auxDijkstra));
   if(d == NULL) return 0;

   struct noAdj* as;
   int i, j, menor, nd;

   for(vs = G->vertices; vs != NULL; vs = vs->prox) // colocando adjacentes
      if(iguaisVertices(&vs->vert, v))
         for(as = vs->ladj, i = 0; as != NULL; as = as->prox, i++){
            d[i].info.vert = as->vert;
            d[i].info.distancia = as->peso;
            d[i].visitado = 0;
         }

   for(vs = G->vertices; vs != NULL; vs = vs->prox){ // colocando nao adjacentes
      if(iguaisVertices(&vs->vert, v)) continue;

      for(j = 0; j < i; j++)
         if(iguaisVertices(&vs->vert, &d[j].info.vert)) break;

      if(j == i){
         d[i].info.vert = vs->vert;
         d[i].info.distancia = INT_MAX;
         d[i++].visitado = 0;
      }
   }

   for(i = 0; i < G->NumVert - 1; i++){
      for(j = 0; j < G->NumVert - 1 && d[j].visitado; j++);

      for(menor = j, ++j; j < G->NumVert - 1; j++)
         if(!d[j].visitado && d[j].info.distancia < d[menor].info.distancia)
            menor = j;
         
      d[menor].visitado = 1;

      for(vs = G->vertices; vs != NULL; vs = vs-> prox)
         if(iguaisVertices(&d[menor].info.vert, &vs->vert))
            for(as = vs->ladj; as != NULL; as = as->prox){
               if(iguaisVertices(&as->vert, v)) continue;

               for(j = 0; j < G->NumVert - 1 && !iguaisVertices(&as->vert, &d[j].info.vert); j++);

               nd = d[menor].info.distancia == INT_MAX ? INT_MAX : d[menor].info.distancia + as->peso;               
               d[j].info.distancia = nd <= d[j].info.distancia ? nd : d[j].info.distancia;
            }
   }

   *ld = (Distancia)malloc((G->NumVert - 1)*sizeof(struct distancia));
   if(*ld != NULL)
      for(i = 0; i < G->NumVert - 1; i++){
         (*ld)[i].vert = d[i].info.vert;
         (*ld)[i].distancia = d[i].info.distancia; 
      }

   free(d);
   return (*ld != NULL);
}
