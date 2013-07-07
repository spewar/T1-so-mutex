/* 
 * File:   prodcons.c
 * Author: marcelo
 *
 * Created on 26 de Junho de 2013, 16:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include <pthread.h>

/*
 * Funções soma e subtrai servem para testar o mutex
 */

void *soma();
void *subtrai();
int valor;

void main() {
    inic();
    pthread_t som[50], sub[50];
    valor = 0;
    printf("Começo da execução\n");
    int i;
    for (i = 0; i < 50; i++) {
        pthread_create(&som[i], NULL, soma, NULL);
        pthread_create(&sub[i], NULL, subtrai, NULL);
    }
    for (i = 0; i < 50; i++) {
        pthread_join(som[i], NULL);
        pthread_join(sub[i], NULL);
    }
    printf("valor final eh=""%d\n", valor);
}

void *soma() {
    printf("soma\n");
    lock();
    valor = valor + 2;
    unlock();
}

void *subtrai() {
    printf("subtrai\n");
    lock();
    valor--;
    unlock();
}