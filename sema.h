///* 
// * File:   sema.h
// * Author: marcelo
// *
// * Created on 8 de Julho de 2013, 18:20
// */
//
//mutex *initMutex();
typedef struct sema{
  int cont;
  pthread_cond_t cond;
  pthread_mutex_t aux;
}sema;

sema *initSema(int qtd);
void v(sema *s);
void p(sema *s);