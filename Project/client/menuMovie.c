#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

void booking(message *mess, int socketfd)
{
    mess->state = BOOKING;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    printf("%s\n", mess->movie.name);
    printf("%d\n", mess->movie.num);
    for (int i = 0; i < mess->movie.num; i++)
        printf("%d\n", mess->movie.name_len[i]);
    for (int i = 0; i < mess->movie.num; i++)
        printf("%d\n", mess->movie.id[i]);
}

void menuMovie(message *mess, int socketfd)
{
    int choice;
    do
    {
        printf("\n1. Movie Booking\n");
        printf("2. Orders Management\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 2);
    if (choice == 1)
    {
        booking(mess, socketfd);
    }
}