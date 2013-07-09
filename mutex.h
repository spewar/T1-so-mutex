/*
 
 *      Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Silveira, Jhonathan Juncal,  Maicon Cardoso
 *          Mutex em produtor-consumidor
 *                   2013/1
 * 
 */

#include <opa_primitives.h>

//OPA_int_t mut;
//void inicMut();
//void lock();
//void unlock();

typedef struct mutex{
    OPA_int_t mut;
}mutex;

mutex *inicMutex();
void lock(mutex *mut);
void unlock(mutex *mut);