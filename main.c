// checa para saber se é windows OS
// _WIN32 macro
#ifdef _WIN32
    #define limpar "cls"
  
// checa para saber se é linux OS 
// __linux__ macro
#elif __linux__
    #define limpar "clear"
  
#endif

#define TRUE 1
#define MAX 100
#define MAXOP 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grafo.h"

void imprimirListaAdj(Grafo G);
void imprimeListaLista(ListaLista rfc);

int main()
{
  int op, p = 0, t = 0, i = 0;
  char diretorio[MAX], escolha = 0, apagar;
  FILE* fp = NULL;
  Grafo g = NULL;
  struct vertice v1, v2;
  Vertice lv = NULL, v = NULL;
  Distancia ld = NULL;
  ListaLista rfc;

  do{
      do{
          printf("LISTA DE OPCOES:\n\n");
          printf(" [1] Criar grafo nulo.\n");
          printf(" [2] Criar grafo por arquivo.\n");
          printf(" [3] Inserir vértice (v).\n");
          printf(" [4] Inserir arco (v -> w).\n");
          printf(" [5] Remover vértice (v).\n");
          printf(" [6] Remover arco (v -> w).\n");
          printf(" [7] Imprimir grafo.\n");
          printf(" [8] Ver vértice de maior grau.\n");
          printf(" [9] Verificar se existe caminho entre v e w.\n");
          printf("[10] Dado v, verificar todos os menores caminhos a outros vértices.\n");
          printf("[11] Busca em profundidade a partir de v.\n");
          printf("[12] Verificar recursos fortemente conectados.\n");
          printf("[13] Esvaziar grafo (deixar na condição de grafo vazio).\n");
          printf("[14] Anular grafo (deixar na condição de grafo nulo).\n");
          printf("[15] Destruir grafo.\n");
          printf("[16] Sair do sistema.\n");
          printf("\nDigite uma das opcoes: ");
          
          scanf("%d", &op);
          system(limpar);
          setbuf(stdin, NULL);
          
          if(op < 1 || op > MAXOP){
              printf("Opcao invalida! Digite novamente!\n\n");
          }
      } while(op < 1 || op > MAXOP);
      
      if(op == MAXOP){
          break;
      }
      
      switch(op){
          case 1:
            if(g != NULL){
              printf("Destrua o grafo atual primeiro!\n\n");
              break;
            }
            g = criarGrafoNulo();
            printf("Grafo nulo criado com sucesso.\n\n");
            break;

          case 2:
            if(g != NULL){
              printf("Destrua o grafo atual primeiro!\n\n");
              break;
            }

            printf("Entre com o diretório das informações do grafo: ");
            scanf("%s", diretorio);
            fp = fopen(diretorio, "r");
            if(fp == NULL){
              printf("Erro ao abrir arquivo!\n\n");
              break;
            }

            g = criarGrafoNulo();
            fscanf(fp, "%d", &p);
            fscanf(fp, "%d", &t);

            for(i = 0; i < p; i++){
              fscanf(fp, "%s %d %d", v1.nome, &v1.tipo, &v1.acao);
              inserirVertice(g, &v1);
            }

            for(i = 0; i < t; i++){
              fscanf(fp, "%s %d %d %d %s %d %d", v1.nome, &v1.tipo, &v1.acao, &p, v2.nome, &v2.tipo, &v2.acao);
              inserirArco(g, &v1, &v2, p);
            }

            printf("Grafo criado com sucesso!\n\n");
            break;

          case 3:
            if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
            }
            printf("Entre com o nome de v: ");
            scanf("%s", v1.nome);
            printf("Entre com o tipo de v: ");
            scanf("%d", &v1.tipo);
            printf("Entre com a acao de v: ");
            scanf("%d", &v1.acao);
            inserirVertice(g, &v1);
            printf("\n");
            break;

          case 4:
            if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
            }
            printf("Entre com o nome de v: ");
            scanf("%s", v1.nome);
            printf("Entre com o tipo de v: ");
            scanf("%d", &v1.tipo);
            printf("Entre com a acao de v: ");
            scanf("%d", &v1.acao);
            printf("Entre com o nome de w: ");
            scanf("%s", v2.nome);
            printf("Entre com o tipo de w: ");
            scanf("%d", &v2.tipo);
            printf("Entre com a acao de w: ");
            scanf("%d", &v2.acao);
            printf("Entre com o peso (v -> w): ");
            scanf("%d", &p);
            inserirArco(g, &v1, &v2, p);
            printf("\n");
            break;

          case 5:
            if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
            }
            printf("Entre com o nome de v: ");
            scanf("%s", v1.nome);
            printf("Entre com o tipo de v: ");
            scanf("%d", &v1.tipo);
            printf("Entre com a acao de v: ");
            scanf("%d", &v1.acao);
            removerVertice(g, &v1);
            printf("\n");
            break;

          case 6:
            if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
            }
            printf("Entre com o nome de v: ");
            scanf("%s", v1.nome);
            printf("Entre com o tipo de v: ");
            scanf("%d", &v1.tipo);
            printf("Entre com a acao de v: ");
            scanf("%d", &v1.acao);
            printf("Entre com o nome de w: ");
            scanf("%s", v2.nome);
            printf("Entre com o tipo de w: ");
            scanf("%d", &v2.tipo);
            printf("Entre com a acao de w: ");
            scanf("%d", &v2.acao);
            removerArco(g, &v1, &v2);
            printf("\n");
            break;

          case 7:
            if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
            }
            printf("Qtd vértices: %d - Qtd arestas: %d\n\n", g->NumVert, g->NumArco);
            imprimirListaAdj(g);
            break;

          case 8:
            if(!maiorGrau(g, &v1, &p)){
              printf("Grafo invalido!\n\n");
              break;
            }
            printf("\ngrau((\"%s\", %d, %d)) = %d.\n\n", v1.nome, v1.tipo, v1.acao, p);
            break;

            case 9:
              if(g == NULL){
                printf("Crie um grafo primeiro!\n\n");
                break;
              }
              printf("Entre com o nome de v: ");
              scanf("%s", v1.nome);
              printf("Entre com o tipo de v: ");
              scanf("%d", &v1.tipo);
              printf("Entre com a acao de v: ");
              scanf("%d", &v1.acao);
              printf("Entre com o nome de w: ");
              scanf("%s", v2.nome);
              printf("Entre com o tipo de w: ");
              scanf("%d", &v2.tipo);
              printf("Entre com a acao de w: ");
              scanf("%d", &v2.acao);

              if(existeCaminho(g, &v1, &v2))
                printf("Existe caminho entre os vértices!\n\n");
              else
                printf("NÃO existe caminho entre os vértices!\n\n");
              break;

            case 10:
              if(g == NULL){
                printf("Crie um grafo primeiro!\n\n");
                break;
              }
              printf("Entre com o nome de v: ");
              scanf("%s", v1.nome);
              printf("Entre com o tipo de v: ");
              scanf("%d", &v1.tipo);
              printf("Entre com a acao de v: ");
              scanf("%d", &v1.acao);

              if(!Dijkstra(g, &v1, &ld)){
                printf("Ocorreu algum erro ao tentar achar todas distâncias!\n\n");
                break;
              }

              system(limpar);
              for(p = 0; p < g->NumVert - 1; p++)
                if(ld[p].distancia == INT_MAX)
                  printf("dist((\"%s\", %d, %d), (\"%s\", %d, %d)) = Infinito.\n", v1.nome, v1.tipo, v1.acao, ld[p].vert.nome, ld[p].vert.tipo, ld[p].vert.acao);
                else
                  printf("dist((\"%s\", %d, %d), (\"%s\", %d, %d)) = %d.\n", v1.nome, v1.tipo, v1.acao, ld[p].vert.nome, ld[p].vert.tipo, ld[p].vert.acao, ld[p].distancia);
              
              printf("\n\n");
              free(ld);
              break;

            case 11:
              if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
              }
              printf("Entre com o nome de v: ");
              scanf("%s", v1.nome);
              printf("Entre com o tipo de v: ");
              scanf("%d", &v1.tipo);
              printf("Entre com a acao de v: ");
              scanf("%d", &v1.acao);

              if(!BuscaEmProfundidade(g, &v1, &lv, &t)){
                printf("Ocorreu algum erro ao tentar buscar!\n\n");
                break;
              }

              system(limpar);
              for(p = 0; p < t; p++)
                printf("(\"%s\", %d, %d).\n", lv[p].nome, lv[p].tipo, lv[p].acao);

              printf("\n");
              free(lv);
              break;

            case 12:
              Kosaraju(g, &rfc);
              imprimeListaLista(rfc);
              EsvaziaListaLista(&rfc);
              break;

            case 13:
              if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
              }
              EsvaziaGrafo(g);
              printf("Grafo esvaziado!\n\n");
              break;

            case 14:
              if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
              }
              AnulaGrafo(g);
              printf("Grafo anulado!\n\n");
              break;

            case 15:
              if(g == NULL){
              printf("Crie um grafo primeiro!\n\n");
              break;
              }
              ApagaGrafo(&g);
              printf("Grafo destruido!\n\n");
              break;
      }  

  } while(op != MAXOP);
  
  system(limpar);
  printf("\nFIM DO PROGRAMA\n");
  return 0;
}

void imprimirListaAdj(Grafo G) { 
   struct noVert *nv;
   struct noAdj *na;
   if (G == NULL)
      return;
   printf("Lista de Adjacencias:\n");
   for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      printf("\nVertice (\"%s\", %d, %d): ", nv->vert.nome, nv->vert.tipo, nv->vert.acao);
      for (na = nv->ladj; na != NULL; na = na->prox)
         printf("(\"%s\", %d, %d) ", na->vert.nome, na->vert.tipo, na->vert.acao); 
   }
   printf("\n\n");
}

void imprimeListaLista(ListaLista rfc){
  int i = 1;
  for(struct NoLista* compc = rfc; compc != NULL; compc = compc->prox, i++){
    printf("Componente[%d] = { ", i);
    for(struct No* v = compc->no; v != NULL; v = v->prox)
      printf("(\"%s\", %d, %d) ", v->vert.nome, v->vert.tipo, v->vert.acao);
    
    printf("}\n");
  }
  printf("\n\n");
}