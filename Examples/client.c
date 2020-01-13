#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> // for close

#define MAXLINE 100    /*max text line length*/
#define SERV_PORT 3000 /*port*/

int socketfd;
enum
{
    SUCCESS,
    FAILURE,
    LOGIN,
    SIGNUP,
    BOOKING,
    ORDERS,
    MOVIE,
    CINEMA,
    TIME,
    SEAT,
    PAY,
    CONFIRM
};

void sendStr(int fd, char *str)
{
    int len;
    len = htonl(strlen(str));
    send(fd, &len, sizeof(len), 0); // Send len of the string
    send(fd, str, strlen(str), 0);  // Send the string
}

void recvStr(int fd, char *str)
{
    int len = 0;
    char content[MAXLINE];

    memset(&content, 0, MAXLINE);
    recv(fd, &len, sizeof(len), 0);
    recv(fd, content, ntohl(len), 0);
    strcpy(str, content);
    // printf("%s\n", str);
}

void sendInt(int fd, int i)
{
    int content = htonl(i);
    send(fd, &content, sizeof(content), 0);
}

int recvInt(int fd)
{
    int num;
    recv(fd, &num, sizeof(num), 0);
    // printf("%d\n", ntohl(num));
    return ntohl(num);
}

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

int main(int argc, char **argv)
{
    char uname[MAXLINE], passwd[MAXLINE], pkg[MAXLINE];

    int state, num, idx, len, re;

    if (argc != 2)
    {
        perror("[-]Missing IP address of the server");
        exit(1);
    }

    connectToServer(argv[1]);
    printf("Account: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", passwd);

    sendInt(socketfd, LOGIN);

    sendStr(socketfd, uname);
    sendStr(socketfd, passwd);

    re = recvInt(socketfd);

    if (re == SUCCESS)
    {
        sendInt(socketfd, BOOKING);

        sendInt(socketfd, MOVIE);

        num = recvInt(socketfd);

        for (int i = 0; i < num; i++)
        {
            idx = recvInt(socketfd);
            printf("%d - ", idx);
            recvStr(socketfd, pkg);
            printf("%s\n", pkg);
        }

        sendInt(socketfd, 9);
        sendStr(socketfd, "Joker");
    }
    return 0;
}