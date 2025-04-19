#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

int selectCity();
int selectCinema(int cityChoice);
int selectGenre();
int selectMovie(int genreChoice);
void printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice);

#endif