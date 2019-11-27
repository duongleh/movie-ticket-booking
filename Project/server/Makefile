CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: server

server: server.o booking.o
	${CC} server.o booking.o -o server

booking.o: booking.c
	${CC} ${CFLAGS} booking.c

server.o: server.c
	${CC} ${CFLAGS} server.c

clean:
	rm -f *.o *~

