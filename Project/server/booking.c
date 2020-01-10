#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

void sendListMovies(int socketfd)
{
    char *num = "4";
    char *name[] = {"Frozen", "Avenger", "IT", "Joker"};
    char *id[] = {"1", "2", "4", "9"};
    // int name_len[] = {6, 7, 2, 5};

    char pkg[256];
    // memset(mess, 0, sizeof(message));
    // mess->movie.num = 4;
    // memcpy(mess->movie.id, id, sizeof id);
    // strcpy(mess->movie.name, "FrozenAvengerITJoker");
    // memcpy(mess->movie.name_len, name_len, sizeof name_len);
    // strcpy(pkg, num);
    // send(socketfd, pkg, sizeof(pkg), 0);
    int x = atoi(num);
    for (int i = 0; i < x; i++)
    {
        strcpy(pkg, name[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
        strcpy(pkg, id[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
    }
}

void sendListCinemas(message *mess, int socketfd)
{
    int id[] = {11, 23, 37};
    int name_len[] = {12, 12, 14};

    memset(mess, 0, sizeof(message));
    mess->cinema.num = 3;
    memcpy(mess->cinema.id, id, sizeof id);
    strcpy(mess->cinema.name, "CGV Ba TrieuRap Quoc GiaLotte Keangnam");
    memcpy(mess->cinema.name_len, name_len, sizeof name_len);
    send(socketfd, mess, sizeof(message), 0);
}

void sendListTimes(message *mess, int socketfd)
{
    int id[] = {1, 2, 3, 4};
    int name_len[] = {5, 5, 5, 5};

    memset(mess, 0, sizeof(message));
    mess->time.num = 4;
    memcpy(mess->time.id, id, sizeof id);
    strcpy(mess->time.name, "08:3014:5019:1523:25");
    memcpy(mess->time.name_len, name_len, sizeof name_len);
    send(socketfd, mess, sizeof(message), 0);
}

void sendListSeats(message *mess, int socketfd)
{
    int id[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int status[] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0};

    memset(mess, 0, sizeof(message));
    mess->seat.row = 3;
    mess->seat.col = 4;
    memcpy(mess->seat.id, id, sizeof id);
    memcpy(mess->seat.status, status, sizeof status);
    send(socketfd, mess, sizeof(message), 0);
}

void sendListPayments(message *mess, int socketfd)
{
    int id[] = {1, 2};
    int name_len[] = {28, 17};

    memset(mess, 0, sizeof(message));
    mess->pay.num = 2;
    memcpy(mess->pay.id, id, sizeof id);
    strcpy(mess->pay.name, "Thanh toan truc tiep tai rapThanh toan online");
    memcpy(mess->pay.name_len, name_len, sizeof name_len);
    send(socketfd, mess, sizeof(message), 0);
}

void confirmOrder(message *mess, int socketfd)
{
    memset(mess, 0, sizeof(message));
    send(socketfd, mess, sizeof(message), 0);
}