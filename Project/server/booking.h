#ifndef BOOKING_H
#define BOOKING_H
#include "../lib/message.h"

void sendListMovies(message *mess, int socketfd);
void sendListCinemas(message *mess, int socketfd);
void sendListTimes(message *mess, int socketfd);
void sendListSeats(message *mess, int socketfd);
void sendListPayments(message *mess, int socketfd);
void confirmOrder(message *mess, int socketfd);
#endif
