#include <stddef.h>
#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) { 
  if(t==NULL){
    return;
  }
  //hacemos recorrido inorden
  asignarPrev(t->izq, pprev);
  //agregamos ayuda enunciado
  t->prev=*pprev;
  t->prox = NULL;
  if(*pprev!=NULL){
    (*pprev)->prox=t;
  }
  *pprev=t;
  asignarPrev(t->der,pprev);
}
