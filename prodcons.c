/*
 
 *      Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Silveira, Jhonathan Juncal,  Maicon Cardoso
 *          Mutex em produtor-consumidor
 *                   2013/1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include <pthread.h>
#include "fila.h"
/*
 * Funções soma e subtrai servem para testar o mutex
 */

// prototipos das funções utilizadas
void *produtor();
void *consumidor();

void main() {
    inicFila();
    inic();
     int i;
    pthread_t prod[50], prod2[50], cons[50];
    printf("Começo da execução\n");
    for (i = 0; i < 10; i++) {
        pthread_create(&prod[i], NULL, produtor, NULL);
        pthread_create(&cons[i], NULL, consumidor, NULL);
    }
    for (i = 0; i < 10; i++) {
        pthread_create(&prod2[i+10], NULL, produtor, NULL);
    }
    for (i = 0; i < 10; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
        pthread_join(prod2[i+10], NULL);
    }
    printf("\n\nFila apos execução é\n");
    for (i = 0; i < TAM; i++)
        printf("[%c]", buffer[i]);
    printf("\n");
}

/* função bloqueia acesso a fila circular e coloca um char m na fila
 */
void *produtor() {
    lock();
    printf("Produtor criado\n");
    while (bufferCheio()){
        unlock();
        printf("Fila cheia\n");
        lock();
    }
    inserir('m');
    unlock();
}

/* função bloqueia acesso a fila circular e retira um char da mesma
 */
void *consumidor() {
    lock();
    printf("Consumidor criado\n");
    while (bufferVazio()){
        unlock();
        printf("Fila vazia\n");
        lock();
    }
    remover();
    unlock();
}