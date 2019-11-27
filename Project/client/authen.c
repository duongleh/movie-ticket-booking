#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

int requestLogIn(message *mess, int socketfd)
{
    mess->state = LOGIN;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    return mess->state;
}

int logIn(message *mess, int socketfd)
{
    memset(&mess->user, '\0', sizeof(mess->user));
    printf("Account: ");
    scanf("%s", mess->user.name);
    printf("Password: ");
    scanf("%s", mess->user.password);
    return requestLogIn(mess, socketfd);
}