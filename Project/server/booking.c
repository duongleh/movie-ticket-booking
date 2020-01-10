#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

char pkg[256];

void sendListMovies(int socketfd)
{
    int num = 4;
    char *name[] = {"Frozen", "Avenger", "IT", "Joker"};
    char *id[] = {"1", "2", "4", "9"};

    send(socketfd, &num, sizeof(num), 0);

    for (int i = 0; i < num; i++)
    {
        strcpy(pkg, name[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
        strcpy(pkg, id[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
    }
}

void sendListCinemas(int socketfd)
{
    int num = 3;
    char *name[] = {"CGV Ba Trieu", "Rap Quoc Gia", "Lotte Keangnam"};
    char *id[] = {"17", "24", "36"};
    send(socketfd, &num, sizeof(num), 0);

    for (int i = 0; i < num; i++)
    {
        strcpy(pkg, name[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
        strcpy(pkg, id[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
    }
}

void sendListTimes(int socketfd)
{
    int num = 4;
    char *name[] = {"08:30", "14:50", "19:15", "23:25"};
    char *id[] = {"1", "2", "3", "4"};

    send(socketfd, &num, sizeof(num), 0);

    for (int i = 0; i < num; i++)
    {
        strcpy(pkg, name[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
        strcpy(pkg, id[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
    }
}

void sendListSeats(int socketfd)
{
    int row = 3;
    int col = 4;
    char *status[] = {"0", "0", "0", "0", "0", "1", "1", "0", "0", "1", "1", "0"};
    char *id[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};

    send(socketfd, &row, sizeof(row), 0);
    send(socketfd, &col, sizeof(col), 0);

    for (int i = 0; i < row * col; i++)
    {
        strcpy(pkg, status[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
        strcpy(pkg, id[i]);
        send(socketfd, pkg, sizeof(pkg), 0);
    }
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