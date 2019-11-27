#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

void sendListMovies(message *mess, int socketfd)
{
    int id[] = {1, 2, 3, 4};
    int name_len[] = {6, 7, 2, 5};

    mess->movie.num = 4;
    memcpy(mess->movie.id, id, sizeof id);
    strcpy(mess->movie.name, "FrozenAvengerITJoker");
    memcpy(mess->movie.name_len, name_len, sizeof name_len);
    mess->state = MOVIE;

    send(socketfd, mess, sizeof(message), 0);
}