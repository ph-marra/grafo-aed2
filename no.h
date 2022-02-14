#ifndef _NO_H
#define _NO_H
#endif

#ifndef _VERTICE_H
#define _VERTICE_H
#include "vertice.h"
#endif

typedef struct No{
   struct vertice vert;
   struct No *prox;
} No;