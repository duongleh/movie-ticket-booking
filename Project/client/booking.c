#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../lib/message.h"
#include "function.h"

char selectedMovie[100];
char selectedCinema[100];
char selectedTime[100];
int selectedSeat[100];
int numSeatSelected;
char selectedPay[100];
char selectedPayment[100];
char card[100];
char valid_date[100];
int ccv;

void confirmOrder(message *mess, int socketfd)
{
    memset(mess, 0, sizeof(message));
    mess->state = CONFIRM;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    printf("\n%s\n", selectedMovie);
    printf("%s\n", selectedCinema);
    printf("%s\n", selectedTime);
    printf("Seats:");
    for (int i = 0; i < numSeatSelected; i++)
    {
        printf(" %d", selectedSeat[i]);
    }
    printf("\n%s\n", selectedPay);
    if (strcmp(selectedPay, "Thanh toan online") == 0)
    {
        printf("Card Number: %s\n", card);
        printf("Date expire: %s\n", valid_date);
        printf("CCV: %d\n", ccv);
    }
}

void selectPayment(message *mess, int socketfd)
{
    int select, start, valid = 0;
    char payName[100];

    do
    {
        printf("\n");
        start = 0;
        for (int i = 0; i < mess->pay.num; i++)
        {
            subStr(mess->pay.name, payName, start, start + mess->pay.name_len[i] - 1);
            start += mess->pay.name_len[i];
            printf("%d- %s\n", mess->pay.id[i], payName);
        }
        printf("Please enter the ID of payment type: ");
        scanf("%d", &select);
        if (valueInArr(select, mess->pay.id, mess->pay.num) == 0)
        {
            printf("ID is invalid !\n");
        }
        else
            valid = 1;
    } while (valid == 0);
    getName(mess->pay.name, selectedPay, mess->pay.num, select, mess->pay.name_len, mess->pay.id);

    memset(mess, 0, sizeof(message));
    mess->state = PAY;
    mess->pay.choice = select;

    if (select == 2)
    {
        printf("Card Number: ");
        scanf("%s", card);
        printf("Date expire: ");
        scanf("%s", valid_date);
        printf("CCV: ");
        scanf("%d", &ccv);
    }

    strcpy(mess->pay.card, card);
    strcpy(mess->pay.valid_date, valid_date);
    mess->pay.ccv = ccv;
    send(socketfd, mess, sizeof(message), 0);
    confirmOrder(mess, socketfd);
}

void selectSeat(message *mess, int socketfd)
{
    int valid, count = 0;
    char status;

    printf("\nCinema 1\n");
    for (int i = 0; i < mess->seat.row * mess->seat.col; i++)
    {
        status = mess->seat.status[i] == 0 ? '-' : 'x';
        printf("%2d: %c\t", mess->seat.id[i], status);
        count++;
        if (count == mess->seat.col)
        {
            count = 0;
            printf("\n");
        }
    }
    printf("Please enter number of seat you want to book: ");
    scanf("%d", &numSeatSelected);
    for (int i = 1; i <= numSeatSelected; i++)
    {
        valid = 0;
        do
        {
            printf("Please enter the ID of seat no.%d: ", i);
            scanf("%d", &selectedSeat[i - 1]);
            if ((valueInArr(selectedSeat[i - 1], mess->seat.id, mess->seat.row * mess->seat.col) == 0) || (mess->seat.status[selectedSeat[i - 1] - 1] == 1))
            {
                printf("ID is invalid or seat is already taken!\n");
            }
            else
                valid = 1;
        } while (valid == 0);
    }

    memset(mess, 0, sizeof(message));
    mess->state = SEAT;
    memcpy(mess->seat.choice, selectedSeat, sizeof selectedSeat);
    mess->seat.numChoice = numSeatSelected;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    selectPayment(mess, socketfd);
}

void selectTime(message *mess, int socketfd)
{
    int select, start, valid = 0;
    char timeName[100];

    do
    {
        printf("\n");
        start = 0;
        for (int i = 0; i < mess->time.num; i++)
        {
            subStr(mess->time.name, timeName, start, start + mess->time.name_len[i] - 1);
            start += mess->time.name_len[i];
            printf("%d- %s\n", mess->time.id[i], timeName);
        }
        printf("Please enter the ID of time: ");
        scanf("%d", &select);
        if (valueInArr(select, mess->time.id, mess->time.num) == 0)
        {
            printf("ID is invalid !\n");
        }
        else
            valid = 1;
    } while (valid == 0);
    getName(mess->time.name, selectedTime, mess->time.num, select, mess->time.name_len, mess->time.id);

    memset(mess, 0, sizeof(message));
    mess->state = TIME;
    mess->time.choice = select;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    selectSeat(mess, socketfd);
}

void selectCinema(message *mess, int socketfd)
{
    int select, start, valid = 0;
    char cinemaName[100];

    do
    {
        printf("\n");
        start = 0;
        for (int i = 0; i < mess->cinema.num; i++)
        {
            subStr(mess->cinema.name, cinemaName, start, start + mess->cinema.name_len[i] - 1);
            start += mess->cinema.name_len[i];
            printf("%d- %s\n", mess->cinema.id[i], cinemaName);
        }
        printf("Please enter the ID of cinema: ");
        scanf("%d", &select);
        if (valueInArr(select, mess->cinema.id, mess->cinema.num) == 0)
        {
            printf("ID is invalid !\n");
        }
        else
            valid = 1;
    } while (valid == 0);

    getName(mess->cinema.name, selectedCinema, mess->cinema.num, select, mess->cinema.name_len, mess->cinema.id);

    memset(mess, 0, sizeof(message));
    mess->state = CINEMA;
    mess->cinema.choice = select;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    selectTime(mess, socketfd);
}

void selectMovie(message *mess, int socketfd)
{
    int select, start, valid = 0;
    char movieName[100];

    do
    {
        printf("\n");
        start = 0;
        for (int i = 0; i < mess->movie.num; i++)
        {
            subStr(mess->movie.name, movieName, start, start + mess->movie.name_len[i] - 1);
            start += mess->movie.name_len[i];
            printf("%d- %s\n", mess->movie.id[i], movieName);
        }
        printf("Please enter the ID of movie: ");
        scanf("%d", &select);
        if (valueInArr(select, mess->movie.id, mess->movie.num) == 0)
        {
            printf("ID is invalid !\n");
        }
        else
            valid = 1;
    } while (valid == 0);

    getName(mess->movie.name, selectedMovie, mess->movie.num, select, mess->movie.name_len, mess->movie.id);

    memset(mess, 0, sizeof(message));
    mess->state = MOVIE;
    mess->movie.choice = select;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    selectCinema(mess, socketfd);
}

void requestBooking(message *mess, int socketfd)
{
    memset(mess, 0, sizeof(message));
    mess->state = BOOKING;
    send(socketfd, mess, sizeof(message), 0);
    recv(socketfd, mess, sizeof(message), 0);
    selectMovie(mess, socketfd);
}

void booking(message *mess, int socketfd)
{
    int choice;
    do
    {
        printf("\n1. Movie Booking\n");
        printf("2. Orders Management\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 2);
    if (choice == 1)
    {
        requestBooking(mess, socketfd);
    }
}