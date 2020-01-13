CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 
LIB = ../lib

all: client

client: client.o authen.o booking.o function.o
	${CC} client.o authen.o booking.o function.o -o client

client.o: client.c
	${CC} ${CFLAGS} client.c

authen.o: authen.c
	${CC} ${CFLAGS} authen.c

booking.o: booking.c
	${CC} ${CFLAGS} booking.c

function.o: ${LIB}/function.c
	${CC} ${CFLAGS} ${LIB}/function.c

clean:
	rm -f *.o *~

