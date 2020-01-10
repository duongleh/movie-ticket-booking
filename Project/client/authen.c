#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

#define MAXLINE 4096
int state;

int logIn(int socketfd)
{
    char uname[MAXLINE], passwd[MAXLINE], pkg[256];
    state = LOGIN;
    printf("Account: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", passwd);

    send(socketfd, &state, sizeof(state), 0);
    send(socketfd, uname, MAXLINE, 0);
    send(socketfd, passwd, MAXLINE, 0);

    recv(socketfd, pkg, sizeof(pkg), 0);
    return atoi(pkg);
}