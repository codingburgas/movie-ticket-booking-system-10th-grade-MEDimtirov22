#pragma once

#include "structs.h"

int selectCity();
int selectCinema(int cityChoice);
int selectGenre();
int selectMovie(int genreChoice);
void printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice);