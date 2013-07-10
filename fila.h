/*
 *
 *       Universidade Federal de Pelotas
 *           Sistemas Operacionais 
 * Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
 *        Mutex em produtor-consumidor
 *                 2013/1
 * 
 */

#define TAM 5 // define o tamanho maximo da fila

int qtdChar;      // numero de char na fila
int ultimoLido;   // posição do ultimo char lido
int ultimoInserido;  // posiçao do ultimo char colocado
char buffer[TAM]; //buffer onde serão inseridos e removidos os elementos

void inicFila();
void inserir(char c);
void remover(void);
int bufferCheio(void);
int bufferVazio(void);
