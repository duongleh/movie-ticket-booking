#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct time_table
{
    char code[10];
    char course[40];
    int week_day;
    int am_pm;
    int period_start;
    int period_end;
    char week[20];
    char room[10];
} time_table;

int readFile(char courses[100][100], char fileName[20]);
void processData(struct time_table *timeTable, char courses[100][100], int size);
void printTimeTable(struct time_table *timeTable, int size)
{
    char am_pm[10];
    printf("|%-10s|%-40s|%-10s|%-10s|%-8s|%-20s|%-10s\n", "Code", "Course", "Week Day", "AM / PM", "Period", "Week", "Room");
    for (int i = 0; i < size; i++)
    {
        strcpy(am_pm, timeTable[i].am_pm == 1 ? "Morning" : "Afternoon");
        printf("|%-10s|%-40s|%-10d|%-10s|%d - %-4d|%-20s|%-10s\n", timeTable[i].code, timeTable[i].course, timeTable[i].week_day, am_pm,
               timeTable[i].period_start, timeTable[i].period_end, timeTable[i].week, timeTable[i].room);
    }
}

int main()
{
    char courses[100][100];
    char fileName[] = "schedule.txt";
    int size;

    size = readFile(courses, fileName);
    time_table *timeTable = malloc(size * sizeof(time_table));
    processData(timeTable, courses, size);
    printTimeTable(timeTable, size);
    free(timeTable);
    return 0;
}

int readFile(char courses[100][100], char fileName[20])
{
    FILE *fptr;
    int c, count = 0, i = 0;

    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("Error reading file\n");
        exit(-1);
    }

    c = fgetc(fptr);
    while (!feof(fptr))
    {
        switch (c)
        {
        case '\n':
            break;
        case ';':
            i = 0;
            count++;
            break;
        default:
            courses[count][i] = c;
            i++;
            break;
        }
        c = fgetc(fptr);
    }

    fclose(fptr);
    return count;
}

void processData(struct time_table *timeTable, char courses[100][100], int size)
{
    char *token, *token2, course[100][100], detail[100][100];
    int i, j, k;
    for (i = 0; i < size; i++, j = 0, k = 1)
    {
        token = strtok(courses[i], " ");
        while (token != NULL)
        {
            strcpy(course[j++], token);
            token = strtok(NULL, " ");
        }

        strcpy(timeTable[i].code, course[0]);
        strcpy(timeTable[i].course, course[1]);

        while (++k != j - 1)
        {
            strcat(timeTable[i].course, " ");
            strcat(timeTable[i].course, course[k]);
        }

        k = 0;
        token2 = strtok(course[j - 1], ",");
        while (token2 != NULL)
        {
            strcpy(detail[k++], token2);
            token2 = strtok(NULL, ",");
        }

        timeTable[i].week_day = detail[1][0] - '0';
        timeTable[i].am_pm = detail[1][1] - '0';
        timeTable[i].period_start = detail[1][2] - '0';
        timeTable[i].period_end = detail[2][2] - '0';
        strcpy(timeTable[i].week, detail[3]);
        j = 3;

        while (++j != k - 1)
        {
            strcat(timeTable[i].week, ", ");
            strcat(timeTable[i].week, detail[j]);
        }
        strcpy(timeTable[i].room, detail[k - 1]);
    }
}