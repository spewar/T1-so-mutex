/*
 
 *      Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Silveira, Jhonathan Juncal,  Maicon Cardoso
 *          Mutex em produtor-consumidor
 *                   2013/1
 * 
 */

#include <opa_primitives.h>

OPA_int_t mut;
void inicMut();
void lock();
void unlock();