#ifndef BOOKING_H
#define BOOKING_H
#include "../lib/message.h"

void booking(message *mess, int socketfd);
void requestBooking(message *mess, int socketfd);
void selectMovie(message *mess, int socketfd);
void selectCinema(message *mess, int socketfd);
void selectTime(message *mess, int socketfd);
void selectSeat(message *mess, int socketfd);
void selectPayment(message *mess, int socketfd);
void confirmOrder(message *mess, int socketfd);
#endif