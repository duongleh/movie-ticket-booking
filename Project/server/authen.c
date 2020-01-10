#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"

#define MAXLINE 4096

void logIn(int socketfd)
{
    char pkg[256], uname[MAXLINE], passwd[MAXLINE];
    recv(socketfd, uname, sizeof(uname), 0);
    recv(socketfd, passwd, sizeof(passwd), 0);
    printf("%s\n", uname);
    // puts(uname);
    // puts(passwd);
    sprintf(pkg, "%d", SUCCESS);
    send(socketfd, pkg, sizeof(pkg), 0);
}