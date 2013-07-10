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
    teste = inicMutex();   // o mutex teste é inicializado com o valor um
    mut = inic2Mutex();    // o mutex mut é inicializado com o valor zero
    mut2 = inic2Mutex();   // o mutex mut2 é inicializado com o valor zero
    livre = inicSema(TAM); // o semaphoro livre é inicializado com o tamanho da fila
    ocupado = inicSema(0); // o semaphoro livre é inicializado com zero
    int i;
    pthread_t prod[50], cons[50], prod2[50];
    printf("Começo da execução\n");
    // aqui são criadas as threads
    for (i = 0; i < Quant; i++) {
        pthread_create(&prod[i], NULL, produtor, NULL);
        pthread_create(&prod2[i], NULL, produtor, NULL);
        pthread_create(&cons[i], NULL, consumidor, NULL);
    }
    //aqui são sincronizadas as threads
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
    int cont = 0;
    p(livre, mut); // posições livres é decrementado
    lock(teste);   // é trancado o acesso a fila
    printf("Produtor criado\n");
    /* se o buffer esta cheio o acesso é liberado o acesso ao mesmo e trancado novamente
    desta forma uma thread consumidor pode entrar e liberar uma posição no buffer */
    while (bufferCheio()) {
        unlock(teste); // libera acesso a fila
        printf("Fila cheia\n");
        cont++;
        /* após 5 mil testes a thread é finalizada, pois podem existir mais consumidores
         que produtores e isso ocasionaria um loop infinito */
        if (cont == 5000) {
            printf("Thread Finalizada\n");
            break;
        }
        lock(teste); // tranca acesso a fila
    }
    inserir('m');
    unlock(teste); // libera acesso a fila
    v(ocupado, mut2); // incrementa o numero de posições ocupadas
}

/* função bloqueia acesso a fila circular e retira um char da mesma
 */
void *consumidor() {
    int cont = 0;
    printf("Consumidor criado\n");
    p(ocupado, mut2); // o numero de posições ocupadas é decrementado
    lock(teste); // tranca acesso a fila
    printf("Consumidor criado\n");
    /* se o buffer esta vazio o acesso é liberado o acesso ao mesmo e trancado novamente
     desta forma uma thread consumidor pode entrar e liberar uma posição no buffer */
    while (bufferVazio()) {
        unlock(teste); // libera acesso a fila
        printf("Fila vazia\n");
        cont++;
        /* após 5 mil testes a thread é finalizada, pois podem existir mais consumidores
         que produtores e isso ocasionaria um loop infinito */
        if (cont == 5000) {
            printf("Thread Finalizada\n");
            break;
        }
        lock(teste); // tranca acesso a fila
    }
    remover();
    unlock(teste); // libera acesso a fila
    v(livre, mut); // o numero de posições livre é incrementado
}