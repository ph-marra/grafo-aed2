#include "vertice.h"
#include <string.h>

int iguaisVertices(Vertice v1, Vertice v2){
   return(!strcmp(v1->nome,v2->nome) && v1->tipo == v2->tipo && v1->acao == v2->acao);
}