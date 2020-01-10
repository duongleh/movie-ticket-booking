#ifndef BOOKING_H
#define BOOKING_H
#include "../lib/message.h"

void booking(int socketfd);
void receiveMovie(int socketfd);
void selectMovie(int socketfd);
void receiveCinema(int socketfd);
void selectCinema(int socketfd);
void receiveTime(int socketfd);
void selectTime(int socketfd);
void receiveSeat(int socketfd);
void selectSeat(int socketfd);
void selectPayment(int socketfd);
void confirmOrder(int socketfd);
#endif