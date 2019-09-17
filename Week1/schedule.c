#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct time_table
{
    char code[10];
    char course[50];
    int week_day;
    int am_pm;
    int period_start;
    int period_end;
    char week[20];
    char room[10];
} time_table;

int readFile(char courses[100][100], char fileName[20]);
void processData(struct time_table *timeTable, char courses[100][100], int size)
{
    char *token, course[100][100], detail[100][100];
    int i, j, k;
    for (i = 0; i < size; i++, j = 0, k = 1)
    {
        // j = 0;
        // k = 1;

        token = strtok(courses[i], " ");
        while (token != NULL)
        {
            strcpy(course[j++], token);
            token = strtok(NULL, " ");
        }
        // printf("%s\n", course[j - 1]);

        strcpy(timeTable[i].code, course[0]);
        strcpy(timeTable[i].course, course[1]);

        while (++k != j - 1)
        {
            // printf("%s\n", course[k]);
            strcat(timeTable[i].course, " ");
            strcat(timeTable[i].course, course[k]);
        }

        // printf("%s\n", timeTable[i].course);
        k = 0;
        token = strtok(courses[j - 1], ",");
        while (token != NULL)
        {
            strcpy(detail[k++], token);
            token = strtok(NULL, ",");
        }

        timeTable[i].week_day = detail[1][0];
        timeTable[i].am_pm = detail[1][1];
        timeTable[i].period_start = detail[1][2];
        timeTable[i].period_end = detail[2][2];
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

int main()
{
    char courses[100][100];
    char fileName[] = "schedule.txt";
    int size;

    size = readFile(courses, fileName);
    // for (int i = 0; i < size; i++)
    // {
    //     printf("%s\n", courses[i]);
    // }
    time_table *timeTable = malloc(size * sizeof(time_table));
    processData(timeTable, courses, size);
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
