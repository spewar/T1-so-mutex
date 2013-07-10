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

//estrutura do tipo semaphoro 2 OPA_int_t que são utilizados para controle
typedef struct sema{
    OPA_int_t valor;
    OPA_int_t block;
}sema;

sema *inicSema(int qtd);
void v(sema *s, mutex *mut);
void p(sema *s, mutex *mut);