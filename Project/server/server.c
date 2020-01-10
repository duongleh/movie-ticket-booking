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
#include "authen.h"

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
    int connfd, n, state;
    pid_t childpid;
    socklen_t clilen;
    char mess[MAXLINE];
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
        printf("[+]%s:%d - Connection accepted\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(socketfd);
            while (1)
            {
                n = recv(connfd, mess, MAXLINE, 0);
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
                state = atoi(mess);
                switch (state)
                {
                case LOGIN:
                    printf("[+]%s:%d - Request login from user", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    // printf("[+]%s:%d - Request login from user %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.user.name);
                    logIn(connfd);
                    printf("[+]%s:%d - Login successful\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    break;
                case SIGNUP:
                    break;
                case ORDERS:
                    break;
                case BOOKING:
                    // sprintf(mess, "%d", 4);
                    // send(connfd, mess, sizeof(mess), 0);
                    printf("[+]%s:%d - Request booking function\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    sendListMovies(connfd);
                    break;
                case MOVIE:
                    // printf("[+]%s:%d - Choose movie %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.movie.choice);
                    sendListCinemas(connfd);
                    break;
                case CINEMA:
                    // printf("[+]%s:%d - Choose cinema %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.cinema.choice);
                    sendListTimes(connfd);
                    break;
                case TIME:
                    // printf("[+]%s:%d - Choose time %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.time.choice);
                    sendListSeats(connfd);
                    break;
                case SEAT:
                    // printf("[+]%s:%d - Choose seat(s)", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    // for (int i = 0; i < mess.seat.numChoice; i++)
                    // {
                    //     printf(" %d", mess.seat.choice[i]);
                    // }
                    // printf("\n");
                    // sendListPayments(&mess, connfd);
                    break;
                case PAY:
                    // printf("[+]%s:%d - Choose payment type %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), mess.pay.choice);
                    // if (mess.pay.choice == 2)
                    // {
                    //     printf("Card Number: %s\n", mess.pay.card);
                    //     printf("Date expire: %s\n", mess.pay.valid_date);
                    //     printf("CCV: %d\n", mess.pay.ccv);
                    // }
                    break;
                case CONFIRM:
                    printf("[+]%s:%d - Confirm\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    confirmOrder(connfd);
                    break;
                default:
                    break;
                }
            }
        }
    }
    close(connfd);
}