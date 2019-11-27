CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: client

client: client.o authen.o menuMovie.o
	${CC} client.o authen.o menuMovie.o -o client

client.o: client.c
	${CC} ${CFLAGS} client.c

authen.o: authen.c
	${CC} ${CFLAGS} authen.c

menuMovie.o: menuMovie.c
	${CC} ${CFLAGS} menuMovie.c

clean:
	rm -f *.o *~

