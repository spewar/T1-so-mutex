///* 
// * File:   sema.c
// * Author: marcelo
// *
// * Created on 8 de Julho de 2013, 18:21
// */
//
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "sema.h"
#include <opa_primitives.h>
#include <pthread.h>

sema *initSema(int qtd){
  sema *aux;
  aux = (sema *) malloc(sizeof(sema));
  if(aux == NULL){
    printf("\nNão foi possivel alocar\n");
    exit(0); // Aborta o programa.
  }
  aux->cont= qtd;
  pthread_cond_init(&aux->cond,NULL);  
  return aux;
}
  
void p (sema *s){
    lock();
      s->cont--;
	if(s->cont < 0){
		pthread_mutex_lock(&s->aux);
		unlock();
		pthread_cond_wait(&s->cond,&s->aux);
		pthread_mutex_unlock(&s->aux);
	}else{
		unlock();
	}
}

void v (sema *s){
    lock();
	s->cont++;
	if(s->cont <=0){
		pthread_mutex_lock(&s->aux);
		pthread_cond_signal(&s->cond);
		pthread_mutex_unlock(&s->aux);
	}
	unlock();
}
