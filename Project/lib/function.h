#ifndef FUNCTION_H
#define FUNCTION_H

void sendStr(int fd, char *str);
void recvStr(int fd, char *str);
void sendInt(int fd, int i);
int recvInt(int fd);

void subStr(char *str, char *buffer, int start, int end);
int valueInArr(int val, int arr[], int size);
void getName(char *str, char *buffer, int size, int selectId, int name_len[], int id[]);
int getIndex(int *arr, int num, int select);
int countAvailableSeats(int id[], int size);
#endif