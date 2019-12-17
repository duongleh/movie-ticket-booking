#include <stdio.h>
#include <string.h>

void subStr(char *str, char *buffer, int start, int end)
{
    int j = 0;
    for (int i = start; i <= end; ++i)
    {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

int valueInArr(int val, int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

void getName(char *str, char *buffer, int size, int selectId, int name_len[], int id[])
{
    int start = 0;

    for (int i = 0; i < size; i++)
    {
        if (id[i] == selectId)
            selectId = i;
    }

    for (int i = 0; i < size; i++)
    {
        if (i == selectId)
            subStr(str, buffer, start, start + name_len[i] - 1);
        start += name_len[i];
    }
}