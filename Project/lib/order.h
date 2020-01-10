#ifndef ORDER_H
#define ORDER_H
typedef struct order
{
    char movie[20];
    int movie_id;
    char cinema[20];
    int cinema_id;
    char time[20];
    int time_id;
    int seat_id[10];
    char pay[20];
    int pay_id;
    char card[20];
    int ccv;
    char valid_date[10];
} order;
#endif