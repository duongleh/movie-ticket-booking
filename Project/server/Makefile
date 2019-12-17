CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: server

server: server.o booking.o authen.o
	${CC} server.o booking.o authen.o -o server

booking.o: booking.c
	${CC} ${CFLAGS} booking.c

server.o: server.c
	${CC} ${CFLAGS} server.c

authen.o: authen.c
	${CC} ${CFLAGS} authen.c

clean:
	rm -f *.o *~

