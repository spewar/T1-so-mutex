/*
 *
 *       Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
 *        Mutex em produtor-consumidor
 *                 2013/1
 * 
 */

#include <pthread.h>

typedef struct sema{
    OPA_int_t valor;
    OPA_int_t mutex;
    OPA_int_t block;
}sema;

sema *inicSema(int qtd);
void v(sema *s, mutex *mut);
void p(sema *s, mutex *mut);