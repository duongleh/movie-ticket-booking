CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 
LIB = ../lib

all: server

server: server.o booking.o authen.o function.o
	${CC} server.o booking.o authen.o function.o -o server

booking.o: booking.c
	${CC} ${CFLAGS} booking.c

server.o: server.c
	${CC} ${CFLAGS} server.c

authen.o: authen.c
	${CC} ${CFLAGS} authen.c

function.o: ${LIB}/function.c
	${CC} ${CFLAGS} ${LIB}/function.c

clean:
	rm -f *.o *~

