/*
 *
 *       Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
 *        Mutex em produtor-consumidor
 *                 2013/1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include <pthread.h>
#include "fila.h"
#include "sema.h"
#define Quant 6  // define o numero de threads que será criado,
                  // caso valor for maior que 50 tem que trocar os vetores das threads

// prototipos das funções utilizadas
void *produtor();
void *consumidor();
mutex *teste, *mut, *mut2;
sema *ocupado, *livre;

void main() {
    inicFila();
    teste = inicMutex();
    mut = inicMutex();
    mut2 = inicMutex();
    livre = inicSema(TAM);
    ocupado = inicSema(0);
    int i;
    pthread_t prod[50], cons[50], prod2[20];
    printf("Começo da execução\n");
    for (i = 0; i < Quant; i++) {
        pthread_create(&prod[i], NULL, produtor, NULL);
        pthread_create(&prod2[i], NULL, produtor, NULL);
        pthread_create(&cons[i], NULL, consumidor, NULL);
    }
    for (i = 0; i < Quant; i++) {
    pthread_join(prod[i], NULL);
    pthread_join(prod2[i], NULL);
    pthread_join(cons[i], NULL);
    }
    printf("\n\nFila apos execução é\n");
    for (i = 0; i < TAM; i++)
        printf("[%c]", buffer[i]);
    printf("\n");
}

/* função bloqueia acesso a fila circular e coloca um char m na fila
 */
void *produtor() {

    //função usando semaphoros 
    p(livre, mut);
    lock(teste);
    printf("Produtor criado\n");
    while (bufferCheio()){
        unlock(teste);
        printf("Fila cheia\n");
        lock(teste);
    }
    inserir('m');
    unlock(teste);
    v(ocupado, mut2);
}

/* função bloqueia acesso a fila circular e retira um char da mesma
 */
void *consumidor() {
    printf("Consumidor criado\n");
 
 
    //função usando semaphoros 
    p(ocupado, mut2);
    lock(teste);
    printf("Consumidor criado\n");
    while (bufferVazio()){
        unlock(teste);
        printf("Fila vazia\n");
        lock(teste);
    }
    remover();
    unlock(teste);
    v(livre, mut);
}