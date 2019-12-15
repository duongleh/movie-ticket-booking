#ifndef AUTHEN_H
#define AUTHEN_H
#include "../lib/message.h"

int logIn(message *mess, int socketfd);
int requestLogIn(message *mess, int socketfd);
#endif