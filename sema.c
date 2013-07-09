///* 
// * File:   sema.c
// * Author: marcelo
// *
// * Created on 8 de Julho de 2013, 18:21
// */
//
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "sema.h"
#include <opa_primitives.h>
#include <pthread.h>

sema *inicSema(int qtd){
    sema *aux;
  aux = (sema *) malloc(sizeof(sema));
  if(aux == NULL){
    printf("\nNão foi possivel alocar\n");
    exit(0);
  }
  aux->cont2= qtd;
  OPA_store_int(&aux->cont, qtd);
  return aux;
}
  
void p (sema *s, mutex *mut){
    lock(mut);
    int i=0;
    while(s->cont2 <= 0){
        unlock(mut);
        lock(mut);
        if(i > 1000){ // caso exista alguma thread trancada após 100 testes ela eh liberada
            unlock(mut);
            break;
        }
    }
    s->cont2--;
    OPA_decr_int(&s->cont);
    unlock(mut);
}
void v (sema *s, mutex *mut){
        lock(mut);
        s->cont2++;
        OPA_incr_int(&s->cont);
        unlock(mut);
}