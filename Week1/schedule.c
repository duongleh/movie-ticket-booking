#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct time_table
{
    char code[10];
    char course[20];
    int week_day;
    int am_pm;
    int period_start;
    int period_end;
    char week[20];
    char room[10];
};

int readFile(char table[100][100][100], char fileName[20]);

int main()
{
    char table[100][100][100];
    char fileName[] = "schedule.txt";
    int fileSize;
    fileSize = readFile(table, fileName);

    return 0;
}

int readFile(char table[100][100][100], char fileName[20])
{
    FILE *fptr;
    int c, i = 0;

    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error reading file\n");
        exit(-1);
    }

    c = fgetc(fptr);
    while (feof(fptr) == 0)
    {
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
    return i;
}
