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
#include "fila.h"

// funções da fila circular

// função que inicializa a fila com zero elementos
void inicFila(){
    qtdChar = 0;
    ultimoLido = 0;
    ultimoInserido = 0;
    int i;
    for (i = 0; i < TAM; i++) // insere vazio em todas posições do buffer
       buffer[i] = 0x20;
}

// coloca o char na fila
void inserir(char c) {
    // atualiza ultimo elemento, e aumenta quantidade de elementos
    if (++ultimoInserido >= TAM) {
        ultimoInserido = 0;
    }
    buffer[ultimoInserido] = c;
    printf("inserido o char %c\n", c);
    qtdChar++;
}

// retira char da fila
void remover(void) {
    if (++ultimoLido >= TAM) {
        ultimoLido = 0;
    }
    printf("retirado o char %c\n", buffer[ultimoLido]);
    // limpa o espaço do char removido
    buffer[ultimoLido] = 0x20;
    qtdChar--;
}

// retorna 1 se o buffer esta cheio e 0 do contrario
int bufferCheio(void) {
    return ultimoLido == ultimoInserido && qtdChar == TAM;
}

// retorna 1 se o buffer esta vazio e 0 do contrario
int bufferVazio(void) {
    return ultimoLido == ultimoInserido && qtdChar == 0;
}

