#include "seating.h"
#include "functions.h"
#include "visualFunctions.h"
#include "loginValidation.h"
#include "userManagement.h"
#include "pch.h"

void mainMenu() {
    BookingSystem bookingSystem;
    SeatingManager seatingManager;

    while (true) {
        clearScreen();
        printLogo("logo.txt");

        std::cout << "1. Start Booking\n";
        std::cout << "2. Log out\n";

        int menuChoice = 0;
        std::cout << "Choice (1-2): ";
        std::cin >> menuChoice;

        if (menuChoice == 2) {
            break;
        }

        if (menuChoice == 1) {
            int cityChoice = bookingSystem.selectCity();
            if (cityChoice == -1) {
                continue;
            }

            int cinemaChoice = bookingSystem.selectCinema(cityChoice);
            if (cinemaChoice == -1) {
                continue;
            }

            int genreChoice = bookingSystem.selectGenre();
            if (genreChoice == -1) {
                continue;
            }

            int movieChoice = bookingSystem.selectMovie(genreChoice);
            if (movieChoice == -1) {
                continue;
            }

            bookingSystem.printBookingDetails(cityChoice, cinemaChoice, movieChoice);

            SeatingLayout layout = seatingManager.createSampleLayout();
            seatingManager.displayLayout(layout);

            seatingManager.bookSeats(layout);

            seatingManager.displayLayout(layout);

            std::vector<Seat> bookedSeats;
            for (int i = 0; i < layout.seats.size(); i++) {
                for (int j = 0; j < layout.seats[i].size(); j++) {
                    if (layout.seats[i][j].isBooked) {
                        bookedSeats.push_back(layout.seats[i][j]);
                    }
                }
            }

            bool isOnlineCustomer = false;
            bookingSystem.completeBooking(cityChoice, cinemaChoice, movieChoice, bookedSeats, isOnlineCustomer);
        }
        else {
            clearScreen();
        }
    }
}