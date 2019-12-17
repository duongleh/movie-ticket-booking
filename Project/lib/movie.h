#ifndef MOVIE_H
#define MOVIE_H
typedef struct movie
{
    int num;
    int id[10];
    char name[256];
    int name_len[10];
    int choice;
} movie;
#endif