/*
 *
 *       Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
 *        Mutex em produtor-consumidor
 *                 2013/1
 * 
 */

#include <opa_primitives.h>


typedef struct mutex{
    OPA_int_t mut;
}mutex;

mutex *inicMutex();
mutex *inic2Mutex();
void lock(mutex *mut);
void unlock(mutex *mut);