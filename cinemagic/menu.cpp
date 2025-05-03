#include "pch.h"
#include "seating.h"
#include "functions.h"
#include "visualFunctions.h"

using namespace std;

void mainMenu() {
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        cout << "1. Start Booking\n";
        cout << "2. Exit\n";

        int choice;
        cout << "Choice (1-2): ";
        cin >> choice;

        if (choice == 2) {
            exitMessage();
            break;
        }

        if (choice == 1) {
            int cityChoice = 0, cinemaChoice = 0, genreChoice = 0, movieChoice = 0;

            while (true) {
                cityChoice = selectCity();
                if (cityChoice == -1) break;

                cinemaChoice = selectCinema(cityChoice);
                if (cinemaChoice == -1) continue;

                genreChoice = selectGenre();
                if (genreChoice == -1) continue;

                movieChoice = selectMovie(genreChoice);
                if (movieChoice == -1) continue;

                printBookingDetails(cityChoice, cinemaChoice, movieChoice);
                SeatingLayout layout = createSampleLayout();
                displayLayout(layout);
                bookSeats(layout);
                displayLayout(layout);

                vector<Seat> selectedSeats;
                for (const auto& row : layout.seats) {
                    for (const auto& seat : row) {
                        if (seat.isBooked) {
                            selectedSeats.push_back(seat);
                        }
                    }
                }

                bool isOnlineCustomer = false;
                completeBooking(cityChoice, cinemaChoice, movieChoice, selectedSeats, isOnlineCustomer);

                break;
            }
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
