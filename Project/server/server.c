#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // for close
#include "../lib/message.h"
#include "booking.h"

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8      /*maximum number of client connections */

int socketfd;
message mess;

void initServer()
{
    struct sockaddr_in servaddr;
    //creation of the socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Server Socket is created.\n");

    //preparation of the socket address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (bind(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("[-]Error in binding.\n");
        exit(1);
    }

    if (listen(socketfd, LISTENQ) == 0)
    {
        printf("[+]Listening....\n");
    }
    else
    {
        printf("[-]Error in binding.\n");
    }
}

int main(int argc, char **argv)
{
    int connfd, n;
    pid_t childpid;
    socklen_t clilen;
    message mess;
    struct sockaddr_in cliaddr;
    initServer();
    while (1)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(socketfd, (struct sockaddr *)&cliaddr, &clilen);
        if (connfd < 0)
        {
            exit(1);
        }
        printf("[+]Connection accepted from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(socketfd);
            while (1)
            {
                n = recv(connfd, &mess, MAXLINE, 0);
                if (n < 0)
                {
                    perror("Read error");
                    exit(1);
                }
                // if (strcmp(mess, ":exit") == 0)
                // {
                //     printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                //     break;
                // }

                // printf("<%s:%d>: \t%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.state);
                switch (mess.state)
                {
                case LOGIN:
                    printf("%s - %s\n", mess.user.name, mess.user.password);
                    memset(&mess, 0, sizeof(mess));
                    mess.state = SUCCESS;
                    send(connfd, &mess, n, 0);
                    break;
                case SIGNUP:
                    break;
                case BOOKING:
                    memset(&mess, 0, sizeof(mess));
                    sendListMovies(&mess, connfd);
                    break;
                case ORDERS:
                    break;
                case SELECT_MOVIE:
                    break;
                case SELECT_CINEMA:
                    break;
                case SELECT_TIME:
                    break;
                case SELECT_SEAT:
                    break;
                case SELECT_PAY:
                    break;
                case CONFIRM:
                    break;
                default:
                    break;
                }
            }
        }
    }
    close(connfd);
}