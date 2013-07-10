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
  OPA_store_int(&aux->valor, qtd);
  return aux;
}
  
void p (sema *s, mutex *mut){
       printf("FunÃ§Ã£o P\n");
        while (OPA_cas_int(&s->mutex, 0, 1)) //Compara e troca a variÃ¡vel mutex, de forma atÃ´mica.
            continue;
        OPA_decr_int(&s->valor); //Decrementa a variÃ¡vel de forma atÃ´mica.
        if (s->valor.v < 0) {
            unlock(mut);
            OPA_store_int(&s->mutex, 0);
            while (OPA_cas_int(&s->block, 0, 1))
                continue;
        } else {
            OPA_store_int(&s->mutex, 0);
        }
}

void v(sema *s, mutex *mut) {
    printf("FunÃ§Ã£o V\n");
    while (OPA_cas_int(&s->mutex, 0, 1)) //Compara e troca a variÃ¡vel mutex, de forma atÃ´mica.
        continue;
    OPA_incr_int(&s->valor); //Incrementa a variÃ¡vel de forma atÃ´mica.
    if (s->valor.v <= 0) {
        while (!s->block.v)
            continue;
        OPA_store_int(&s->block, 0);
    }
    OPA_store_int(&s->mutex, 0);
}