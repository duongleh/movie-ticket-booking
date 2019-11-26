#ifndef SELECT_H
#define SELECT_H
typedef struct select
{
    char movie[20];
    int movie_id;
    char cinema[20];
    int cinema_id;
    long time;
    int time_id;
    int seat_id[10];
    char pay[20];
    int pay_id;
    char card[20];
    int ccv;
    char valid_date[10];
} select;
#endif
