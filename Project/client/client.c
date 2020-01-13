#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../lib/message.h"
#include "authen.h"
#include "booking.h"

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/

int socketfd;
message mess;

void connectToServer(char *ip)
{
    struct sockaddr_in servaddr;
    //Create a socket for the client
    //If socketfd<0 there was an error in the creation of the socket
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[-]Problem in creating the socket");
        exit(2);
    }
    printf("[+]Client Socket is created.\n");

    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(SERV_PORT); //convert to big-endian order

    //Connection of the client to the socket
    if (connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("[-]Problem in connecting to the server");
        exit(3);
    }
    printf("[+]Connected to Server.\n");
}

int menuAuthen()
{
    int choice;
    do
    {
        printf("\n1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);
    return choice;
}

int main(int argc, char **argv)
{
    int choice = 0, re;
    char uname[MAXLINE];
    if (argc != 2)
    {
        perror("[-]Missing IP address of the server");
        exit(1);
    }

    connectToServer(argv[1]);

    choice = menuAuthen();
    switch (choice)
    {
    case 1:
        do
        {
            re = logIn(socketfd, uname);
            if (re != SUCCESS)
                printf("Login fail!\n\n");

        } while (re != SUCCESS);
        printf("\nLogin successful!\n");
        booking(socketfd, uname);
        break;
    case 2:

        break;
    default:
        break;
    }
    // memset(&buffer, 0, sizeof(buffer));
    return 0;
}