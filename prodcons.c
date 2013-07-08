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

#define TAM 9

int qtd_char = 0;      // numero de char na fila
int ultimo_lido = 0;   // posição do ultimo char lido
int ultimo_inserido = 0;  // posiçao do ultimo char colocado

char buffer[TAM];

/*
 * Funções da fila
 */

int buffer_cheio(void);
int buffer_vazio(void);
void inserir(char c);
void remover(void);
void *produtor();
void *consumidor();
/*
 * Funções soma e subtrai servem para testar o mutex
 */

void *soma();
void *subtrai();
int valor;

void main() {
    inic();
   // pthread_t som[50], sub[50];
    int i;
    pthread_t prod[30], prod2[30], cons[30];
    for (i = 0; i < TAM; i++)
       buffer[i] = 0x20;
    valor = 0;
    printf("Começo da execução\n");
    
//    for (i = 0; i < 50; i++) {
//        pthread_create(&som[i], NULL, soma, NULL);
//        pthread_create(&sub[i], NULL, subtrai, NULL);
//    }
//    for (i = 0; i < 50; i++) {
//        pthread_join(som[i], NULL);
//        pthread_join(sub[i], NULL);
//    }
//    printf("valor final eh=""%d\n", valor);
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

// funções da fila circular
// coloca o char na fila
void inserir(char c)
{
    // atualiza ultimo elemento, e aumenta quantidade de elementos
    if (++ultimo_inserido >= TAM){
        ultimo_inserido = 0;
    }
    buffer[ultimo_inserido] = c;
    printf("inserido o char %c\n", c);
    qtd_char++;
}

// retira char da fila
void remover(void)
{
  if (++ultimo_lido >= TAM){
      ultimo_lido = 0;
  }
  printf("retirado o char %c\n", buffer[ultimo_lido]);
  // limpa o espaço do char removido
  buffer[ultimo_lido] = 0x20;
  qtd_char--;
}

// retorna 1 se o buffer esta cheio e 0 do contrario
int buffer_cheio(void)
{
    return ultimo_lido == ultimo_inserido && qtd_char == TAM;
}
// retorna 1 se o buffer esta vazio e 0 do contrario
int buffer_vazio(void)
{
    return ultimo_lido == ultimo_inserido && qtd_char == 0;
}

/* função bloqueia acesso a fila e coloca um char m na fila
 */
void *produtor() {
    lock();
    printf("Produtor criado\n");
    while (buffer_cheio()){
        unlock();
        printf("Fila cheia\n");
        lock();
    }
    inserir('m');
    unlock();
}

/* função bloqueia acesso a fila e retira um char da mesma
 */
void *consumidor() {
    lock();
    printf("Consumidor criado\n");
    while (buffer_vazio()){
        unlock();
        printf("Fila vazia\n");
        lock();
    }
    remover();
    unlock();
}