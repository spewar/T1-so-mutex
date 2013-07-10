#       Universidade Federal de Pelotas
#           Sistemas Operacionais 
# Marcelo Machado, Jhonathan Juncal,  Maicon Cardoso
#        Mutex em produtor-consumidor
#                 2013/1

mutex: mutex.h mutex.c
	gcc mutex.c -c -o mutex.o

lib: fila.o mutex.o
	ar -cru libmutex.a fila.o sema.o mutex.o

sema: sema.h sema.c
	gcc sema.c -c -o sema.o

prod: sema.o mutex.o fila.o
	gcc prodcons.c -Wall -lpthread -L./ -lmutex -o prodcons

fila: fila.h fila.c
	gcc fila.c -c -o fila.o

all: mutex fila lib sema prod

teste: prodcons
	./prodcons
