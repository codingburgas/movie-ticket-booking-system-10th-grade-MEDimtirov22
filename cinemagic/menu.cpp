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

            SeatingLayout layout = seatingManager.createSampleLayout();
            std::vector<Seat> alreadyBookedSeats = bookingSystem.loadBookedSeatsCSV(cityChoice, cinemaChoice, movieChoice);
            for (int i = 0; i < alreadyBookedSeats.size(); i++) {
                int row = alreadyBookedSeats[i].row;
                int col = alreadyBookedSeats[i].col;
                if (row >= 0 && row < layout.seats.size() && col >= 0 && col < layout.seats[row].size()) {
                    layout.seats[row][col].isBooked = true;
                }
            }

            std::vector<std::vector<bool>> wasBooked(layout.seats.size());
            for (int i = 0; i < layout.seats.size(); ++i) {
                wasBooked[i].resize(layout.seats[i].size());
                for (int j = 0; j < layout.seats[i].size(); ++j) {
                    wasBooked[i][j] = layout.seats[i][j].isBooked;
                }
            }

            clearScreen();
            bookingSystem.printBookingDetails(cityChoice, cinemaChoice, movieChoice);

            seatingManager.displayLayout(layout);
            if (!seatingManager.bookSeats(layout)) {
                continue;
            }
            seatingManager.displayLayout(layout);

            std::vector<Seat> bookedNow;
            for (int i = 0; i < layout.seats.size(); i++) {
                for (int j = 0; j < layout.seats[i].size(); j++) {
                    if (!wasBooked[i][j] && layout.seats[i][j].isBooked) {
                        bookedNow.push_back(layout.seats[i][j]);
                    }
                }
            }

            bool isOnlineCustomer = false;
            bookingSystem.completeBooking(cityChoice, cinemaChoice, movieChoice, bookedNow, isOnlineCustomer);
        }
        else {
            clearScreen();
        }
    }
}