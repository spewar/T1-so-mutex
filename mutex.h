/* 
 * File:   mutex.h
 * Author: marcelo
 *
 * Created on 26 de Junho de 2013, 16:08
 */
#include <opa_primitives.h>

void lock (OPA_int_t *y){
    while(1){
                if(OPA_cas_int(y,1,0)) {
			break;
		}
    }
}

void unlock (OPA_int_t *y){
    OPA_store_int(y,1);;
}