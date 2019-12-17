#ifndef PAY_H
#define PAY_H
typedef struct pay
{
    int num;
    int id[10];
    char name[256];
    int name_len[10];
    int choice;
    char card[20];
    int ccv;
    char valid_date[10];
} pay;
#endif