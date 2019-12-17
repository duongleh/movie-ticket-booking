CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: client

client: client.o authen.o booking.o function.o
	${CC} client.o authen.o booking.o function.o -o client

client.o: client.c
	${CC} ${CFLAGS} client.c

authen.o: authen.c
	${CC} ${CFLAGS} authen.c

booking.o: booking.c
	${CC} ${CFLAGS} booking.c

function.o: function.c
	${CC} ${CFLAGS} function.c

clean:
	rm -f *.o *~

