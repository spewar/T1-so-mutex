///* 
// * File:   sema.h
// * Author: marcelo
// *
// * Created on 8 de Julho de 2013, 18:20
// */
//
#include <pthread.h>

typedef struct sema{
    OPA_int_t cont;
    int cont2;
}sema;

sema *inicSema(int qtd);
void v(sema *s, mutex *mut);
void p(sema *s, mutex *mut);