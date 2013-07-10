Universidade Federal de Pelotas
Sistemas Operacionais 
Marcelo Machado, Jhonathan Juncal, Maicon Cardoso
Mutex em produtor-consumidor
2013/1
	
- Implementação de mutex para controle de escrita/leitura numa fila. Utilizou-se
a biblioteca de operações atômicas OpenPA para operações sob as variáveis de controle.
Foi implementado o problema produtor/consumidor com  dois semáforots e um mutex para 
controle das posições livres e das posições ocupadas da fila garantindo acesso único
a seção crítica.

Os semáforos
	- Semáforo livre: inicializa com o tamanho da fila (número de threads que podem ser
	executadas (inserir ou retirar) ao mesmo tempo);
	- Semáforo ocupado: iniciliza com 0 (número de posições ocupadas no começo da execução.
	
O mutex
	- Mutex: inicializado com 1 e, quando dado lock, tranca o acesso, somente sendo liberado
  quando recebido o unlock.
  
O produtor/consumidor
	- Produtor: é dado P no semáforo livre (trancando o acesso a uma posição
	da fila), após ocorre um lock garantindo que somente uma thread acesse a seção crítica, testada
	se a fila está cheia e, se não tiver cheia, insere na fila e dá unlock no mutex e V no semáforo ocupado
	. Se a fila estiver cheia imprime "Fila cheia" na tela, chama unlock e depois chama lock novamente 
	para que possa liberar acesso e outra thread poder consumir o elemento.
	- Consumidor: é dado P no semáforo ocupado (trancando o acesso a uma posição
	da fila), após ocorre um lock garantindo que somente uma thread acesse a seção crítica, testada
	se a fila está vazia e, se não tiver vazia, consome um elemento da fila e dá unlock no mutex e V no 
	semáforo livre. Se a fila estiver cheia imprime "Fila vazia" na tela, chama unlock e chama 
	lock novamente para que possa liberar acesso e outra thread poder consumir o elemento.
        - Se a fila estiver cheia ou vazia 5000 vezes, ocorre um break na função e a thread é encerrada, não 
        testando mais a fila e imprimindo a mensagem "Thread Finalizada".
        - O número de consumidores e produtores é definido no Define Quant do prodcons.c., sendo que
        as threads são criadas no laço for da linha 36.
	
A fila
	- Fila: o tamanho da fila é definido no DEFINE TAM no fila.h. É uma fila de caracteres, possuindo as
	funções inicFila (inicializa a fila vazia), inserir (insere o elemento na fila), remover (remove da fila),
	bufferCheio (retorna 1 se tiver cheio, 0 caso contrário) e bufferVazio (retorna 1 se tiver vazio, 0 caso
	contrário)
	
Testes
	Foram feitos diversos testes, dentre eles:
	- Somente com produtores: retornou a fila completa com as posições utilizadas;
	- Mesmo número de produtores e consumidores: retornou a fila vazia;
	- 12 produtores e 6 consumidores: retornou 6 posições na fila;
	- 12 consumidores e 6 consumidores: retornou fila vazia;
	- 12 produtores, 6 consumidores, 5 posições na fila: retornou fila cheia.
	Não houve nenhum problema de deadlock em nenhum dos casos, e todos os retornos foram os esperados.
	
Makefile
	- Para executar o programa, é necessário entrar na pasta do programa e executar o make all e, após,
	make teste.

Exemplo
        - Está sendo executado (caso não haja alteração no código) o programa com:
            - Tamanho da fila: 6;
            - Número de consumdores: 6;
            - Número de produtores: 12.

Resultado
        - Após a execução, é impresso na tela o resultado final da fila, mostrando cada uma das
        posições e seus respectivos valores.