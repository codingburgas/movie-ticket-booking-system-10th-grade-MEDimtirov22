#pragma once

#include "structs.h"

int selectCity();
int selectCinema(int cityChoice);
int selectGenre();
int selectMovie(int genreChoice);
void completeBooking(int cityChoice, int cinemaChoice, int movieChoice, const vector<Seat>& selectedSeats, bool isOnlineCustomer);
void printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice);