#include <iostream>
#include "functions.h"
#include "visualFunctions.h"

using namespace std;

int main() {
    fullScreen();
    printLogo("logo.txt");

    cout << "Welcome to the Movie Ticket Booking System!\n";

    int cityChoice = selectCity();
    int cinemaChoice = selectCinema(cityChoice);
    int genreChoice = selectGenre();
    int movieChoice = selectMovie(genreChoice);

    printBookingDetails(cityChoice, cinemaChoice, movieChoice);
}