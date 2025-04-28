#include <iostream>
#include "seating.h"
#include "functions.h"
#include "visualFunctions.h"

using namespace std;

void mainMenu() {
    clearScreen();
    printLogo("logo.txt");
    cout << "1. Start Booking\n";
    cout << "2. Exit\n";

    int choice;
    cout << "Choice (1-2): ";
    cin >> choice;

    if (choice == 1) {
        int cityChoice = selectCity();
        int cinemaChoice = selectCinema(cityChoice);
        int genreChoice = selectGenre();
        int movieChoice = selectMovie(genreChoice);
        printBookingDetails(cityChoice, cinemaChoice, movieChoice);
        SeatingLayout layout = createSampleLayout();
        displayLayout(layout);
        bookSeats(layout);
        displayLayout(layout);
    }
    else if (choice == 2) {
        exitMessage();
    }
    else {
        cout << "Invalid choice. Please try again.\n";
        mainMenu();
    }
}