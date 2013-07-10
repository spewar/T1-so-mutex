mutex: mutex.h mutex.c
 gcc mutex.c -c -o mutex.o

queue: queue.h queue.c
 gcc queue.c -c -o queue.o

lib: queue.o mutex.o
 ar -cru libmutex.a queue.o mutex.o

sema: sema.h sema.c
 gcc sema.c -c -o sema.o

prod: sema.o mutex.o queue.o
 gcc prodcons.c -Wall -lpthread -L./ -lmutex -o prodcons

all: mutex queue lib sema prod

teste: prodcons
 ./prodcons