/*
 
 *      Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Silveira, Jhonathan Juncal,  Maicon Cardoso
 *          Mutex em produtor-consumidor
 *                   2013/1
 * 
 */

#include <opa_primitives.h>
#include "mutex.h"

void inic() {
    OPA_store_int(&y, 1);
}

void lock() {
    while (1) {
        if (OPA_cas_int(&y, 1, 0)) {
            break;
        }
    }
}

void unlock() {
    OPA_store_int(&y, 1);
}
