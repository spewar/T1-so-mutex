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
  aux->cont2= qtd;
  OPA_store_int(&aux->cont, qtd);
  return aux;
}
  
void p (sema *s, mutex *mut){
        while (OPA_cas_int(&mut->mut, 0, 1))  // compara e troca a variavel mutex de forma atomica.
             continue;
        OPA_decr_int(&s->valor);  // decrementa a variavel de forma atomica.
        lock(mut);
        if (s->valor.v < 0) {
            unlock(mut);
            OPA_store_int(&mut->mut, 0);
            while (OPA_cas_int(&s->block, 0, 1))
                continue;
        } else {
            OPA_store_int(&mut->mut, 0);
            unlock(mut);
        }
}
void v(sema *s, mutex *mut) {
        printf("FunÃ§Ã£o V\n");
        while (OPA_cas_int(&mut->mut, 0, 1))  // compara e troca a variavel mutex de forma atomica.
                continue;
        OPA_incr_int(&s->valor);  // incrementa a variavel de forma atomica.
        lock(mut);
        if (s->valor.v <= 0) {
                while (!s->block.v)
                        continue;
        unlock(mut);
        OPA_store_int(&s->block, 0);
        }
        OPA_store_int(&mut->mut, 0);
}