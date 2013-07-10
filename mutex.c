/*
 *
 *       Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
 *        Mutex em produtor-consumidor
 *                 2013/1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <opa_primitives.h>
#include "mutex.h"

mutex *inicMutex(){
  mutex *aux;
  aux = (mutex *) malloc(sizeof(mutex));
  if(aux == NULL){
    printf("\nNão foi possivel alocar\n");
    exit(0);
  }
  OPA_store_int(&aux->mut, 1); 
  return aux;
}

void lock(mutex *mut) {
    while (1) {
        if (OPA_cas_int(&mut->mut, 1, 0)) {
            break;
        }
    }
}

void unlock(mutex *mut) {
    OPA_store_int(&mut->mut, 1);
}
