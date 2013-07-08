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

#define TAM 10

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