#ifndef SEAT_H
#define SEAT_H
typedef struct seat
{
    int row;
    int col;
    int id[100];
    int status[100];
    int choice[100];
    int numChoice;
} seat;
#endif