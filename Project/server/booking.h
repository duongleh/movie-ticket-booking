#ifndef BOOKING_H
#define BOOKING_H
#include "../lib/message.h"

void sendListMovies(int socketfd);
void sendListCinemas(int socketfd);
void sendListTimes(int socketfd);
void sendListSeats(int socketfd);
void sendListPayments(int socketfd);
void confirmOrder(int socketfd);
#endif
