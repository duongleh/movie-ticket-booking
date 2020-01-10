#ifndef BOOKING_H
#define BOOKING_H
#include "../lib/message.h"

void booking(int socketfd);
void receiveMovie(int socketfd);
void selectMovie(int socketfd);
void selectCinema(int socketfd);
void selectTime(int socketfd);
void selectSeat(int socketfd);
void selectPayment(int socketfd);
void confirmOrder(int socketfd);
#endif