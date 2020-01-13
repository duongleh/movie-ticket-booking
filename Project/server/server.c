#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "authen.h"
#include "booking.h"
#include "../lib/message.h"
#include "../lib/function.h"

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8      /*maximum number of client connections */

int socketfd;
order ticket;
int child_process_running = 1;

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

void termination_handler(int signum)
{
    child_process_running = 0;
}

int main(int argc, char **argv)
{
    int connfd, n, state;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sigaction new_action, old_action;

    new_action.sa_handler = termination_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(SIGINT, &new_action, &old_action); // Ctrl+C for generating the signal

    initServer();
    while (1)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(socketfd, (struct sockaddr *)&cliaddr, &clilen);
        if (connfd < 0)
        {
            exit(1);
        }
        printf("\n[+]%s:%d - Connection accepted\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(socketfd);
            while (child_process_running)
            {
                n = recv(connfd, &state, sizeof(state), 0);
                if (n < 0)
                {
                    perror("Read error");
                    exit(1);
                }

                if (n == 0)
                {
                    printf("[+]%s:%d - Disconnected\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    exit(0);
                }

                state = ntohl(state);
                switch (state)
                {
                case LOGIN:
                    printf("[+]%s:%d - Request login from user ", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    logIn(connfd);
                    printf("[+]%s:%d - Login successful\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    break;

                case SIGNUP:
                    break;

                case ORDERS:
                    break;

                case BOOKING:
                    printf("\n[+]%s:%d - Request BOOKING\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    setFd(connfd);
                    break;

                case MOVIE:
                    printf("\n[+]%s:%d - Request MOVIE\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    sendListMovies(connfd);
                    ticket.movie_id = recvInt(connfd);
                    recvStr(connfd, ticket.movie);
                    printf("[+]%s:%d - Sent MOVIE\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    printf("[+]%s:%d - Choose movie: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), ticket.movie);
                    break;

                case CINEMA:
                    printf("\n[+]%s:%d - Request CINEMA\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    sendListCinemas(connfd);
                    ticket.cinema_id = recvInt(connfd);
                    recvStr(connfd, ticket.cinema);
                    printf("[+]%s:%d - Sent CINEMA\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    printf("[+]%s:%d - Choose cinema: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), ticket.cinema);
                    break;

                case TIME:
                    printf("\n[+]%s:%d - Request TIME\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    sendListTimes(connfd);
                    ticket.time_id = recvInt(connfd);
                    recvStr(connfd, ticket.time);
                    printf("[+]%s:%d - Sent TIME\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    printf("[+]%s:%d - Choose time: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), ticket.time);
                    break;

                case SEAT:
                    printf("\n[+]%s:%d - Request SEAT\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    sendListSeats(connfd);
                    printf("[+]%s:%d - Sent SEAT\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

                    ticket.seat_num = recvInt(connfd);
                    for (int i = 0; i < ticket.seat_num; i++)
                    {
                        ticket.seat_id[i] = recvInt(connfd);
                    }
                    printf("[+]%s:%d - Choose seat(s):", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    for (int i = 0; i < ticket.seat_num; i++)
                    {
                        printf(" %d", ticket.seat_id[i]);
                    }
                    printf("\n");
                    break;

                case PAY:
                    printf("\n[+]%s:%d - Request PAY\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    ticket.total = FARE * ticket.seat_num;
                    sendListPayments(ticket.total);
                    printf("[+]%s:%d - Sent PAY\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

                    ticket.pay_id = recvInt(connfd);
                    recvStr(connfd, ticket.pay);
                    printf("[+]%s:%d - Choose payment type %d - %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), ticket.pay_id, ticket.pay);
                    if (ticket.pay_id == 2)
                    {
                        recvStr(connfd, ticket.card);
                        recvStr(connfd, ticket.valid_date);
                        ticket.ccv = recvInt(connfd);

                        printf("Card Number: %s\n", ticket.card);
                        printf("Date expire: %s\n", ticket.valid_date);
                        printf("CCV: %d\n", ticket.ccv);
                    }
                    break;

                case CONFIRM:
                    printf("\n[+]%s:%d - Order Confirm\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    confirmOrder();
                    break;

                default:
                    break;
                }
            }
        }
    }
    close(connfd);
}