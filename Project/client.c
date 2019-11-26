#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // for close

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];

    //basic check of the arguments
    if (argc != 2)
    {
        perror("[-]Missing IP address of the server");
        exit(1);
    }

    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[-]Problem in creating the socket");
        exit(2);
    }
    printf("[+]Client Socket is created.\n");

    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(SERV_PORT); //convert to big-endian order

    //Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("[-]Problem in connecting to the server");
        exit(3);
    }
    printf("[+]Connected to Server.\n");

    while (1)
    {
        printf("Client: \t");
        scanf("%s", &buffer[0]);
        send(sockfd, buffer, MAXLINE, 0);

        if (strcmp(buffer, ":exit") == 0)
        {
            close(sockfd);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }

        memset(&buffer, 0, sizeof(buffer));

        if (recv(sockfd, buffer, MAXLINE, 0) < 0)
        {
            printf("[-]Error in receiving data.\n");
        }
        else
        {
            printf("Server: \t%s\n", buffer);
        }
        memset(&buffer, 0, sizeof(buffer));
    }

    return 0;
}