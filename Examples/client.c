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

    state = htonl(LOGIN);
    send(socketfd, &state, sizeof(state), 0);

    len = htonl(strlen(uname));
    send(socketfd, &len, sizeof(len), 0);
    send(socketfd, uname, strlen(uname), 0);

    len = htonl(strlen(passwd));
    send(socketfd, &len, sizeof(len), 0);
    send(socketfd, passwd, strlen(passwd), 0);

    recv(socketfd, &re, sizeof(re), 0);
    printf("%d\n", re);

    state = htonl(BOOKING);
    send(socketfd, &state, sizeof(state), 0);

    // MOVIE
    state = htonl(MOVIE);
    send(socketfd, &state, sizeof(state), 0);

    recv(socketfd, &num, sizeof(num), 0);
    num = ntohl(num);
    printf("%d\n", num);

    for (int i = 0; i < num; i++)
    {
        recv(socketfd, &idx, sizeof(idx), 0);
        printf("%d - ", ntohl(idx));
        recv(socketfd, &len, sizeof(len), 0);
        memset(&pkg, 0, sizeof(pkg));
        recv(socketfd, pkg, ntohl(len), 0);
        printf("%s\n", pkg);
    }

    idx = htonl(9);
    send(socketfd, &idx, sizeof(idx), 0);

    memset(&pkg, 0, sizeof(pkg));
    strcpy(pkg, "Joker");
    len = htonl(strlen(pkg));
    send(socketfd, &len, sizeof(len), 0);
    puts(pkg);
    send(socketfd, pkg, strlen(pkg), 0);
    return 0;
}