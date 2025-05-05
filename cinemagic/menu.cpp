#include "seating.h"
#include "functions.h"
#include "visualFunctions.h"
#include "loginValidation.h"
#include "userManagement.h"
#include "pch.h"

void mainMenu() {
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "1. Start Booking\n";
        std::cout << "2. Log out\n";

        int choice;
        std::cout << "Choice (1-2): ";
        std::cin >> choice;

        if (choice == 2) {
            break;
            clearScreen();
        }

        if (choice == 1) {
            int cityChoice = 0, cinemaChoice = 0, genreChoice = 0, movieChoice = 0;

            while (true) {
                cityChoice = selectCity();
                if (cityChoice == -1) {
                    break;
                }

                cinemaChoice = selectCinema(cityChoice);
                if (cinemaChoice == -1) {
                    continue;
                }

                genreChoice = selectGenre();
                if (genreChoice == -1) {
                    continue;
                }

                movieChoice = selectMovie(genreChoice);
                if (movieChoice == -1) {
                    continue;
                }

                printBookingDetails(cityChoice, cinemaChoice, movieChoice);
                SeatingLayout layout = createSampleLayout();
                displayLayout(layout);
                bookSeats(layout);
                displayLayout(layout);

                std::vector<Seat> selectedSeats;
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
            clearScreen();
        }
    }
}
