#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/message.h"
#include "../lib/function.h"

#define MAXLINE 4096

int logIn(int socketfd, char *uname)
{
    char passwd[MAXLINE];
    int state;

    printf("Account: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", passwd);

    sendInt(socketfd, LOGIN);
    sendStr(socketfd, uname);
    sendStr(socketfd, passwd);
    state = recvInt(socketfd);
    return state;
}