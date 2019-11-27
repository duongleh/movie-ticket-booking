#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

void booking(message *mess, int socketfd)
{
    mess->state = LOGIN;
    send(socketfd, mess, sizeof(message), 0);
    // recv(socketfd, mess, sizeof(message), 0);
    // return mess->state;
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