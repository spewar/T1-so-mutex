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
  OPA_store_int(&aux->valor, qtd); // grava na variavel valor o numero passado por parametro
  return aux;
}
  
void p (sema *s, mutex *mut){
        while (OPA_cas_int(&mut->mut, 0, 1))
            continue;
        OPA_decr_int(&s->valor); //Decrementa a variavel de forma atomica.
        if (s->valor.v < 0) {
            OPA_store_int(&mut->mut, 0);
            while (OPA_cas_int(&s->block, 0, 1)) // tranca a thread
                continue;
        } else {
            OPA_store_int(&mut->mut, 0);
        }
}

void v(sema *s, mutex *mut) {
    while (OPA_cas_int(&mut->mut, 0, 1))
        continue;
    OPA_incr_int(&s->valor); //Incrementa a variavel atomicamente.
    if (s->valor.v <= 0) {
        while (!s->block.v)  // libera a thread
            continue;
        OPA_store_int(&s->block, 0);
    }
    OPA_store_int(&mut->mut, 0);
}