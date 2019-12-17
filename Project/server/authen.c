#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

void logIn(message *mess, int socketfd)
{
    memset(mess, 0, sizeof(message));
    mess->state = SUCCESS;
    send(socketfd, mess, sizeof(message), 0);
}