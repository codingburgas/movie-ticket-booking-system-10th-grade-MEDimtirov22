#include <iostream>
#include "seating.h"
#include "functions.h"
#include "visualFunctions.h"
#include "payment.h" // Include the payment header

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

        // Calculate total amount and display seat pricing
        double totalAmount = 0.0;
        double platinumPrice = 15.0;
        double goldPrice = 10.0;
        double silverPrice = 5.0;
        int platinumCount = 0, goldCount = 0, silverCount = 0;

        for (const auto& row : layout.seats) {
            for (const auto& seat : row) {
                if (seat.isBooked) {
                    if (seat.type == PLATINUM) {
                        totalAmount += platinumPrice;
                        platinumCount++;
                    }
                    else if (seat.type == GOLD) {
                        totalAmount += goldPrice;
                        goldCount++;
                    }
                    else if (seat.type == SILVER) {
                        totalAmount += silverPrice;
                        silverCount++;
                    }
                }
            }
        }

        clearScreen();

        cout << "\nSeat Pricing:\n";
        cout << "Platinum Seats (" << platinumCount << "): $" << platinumCount * platinumPrice << "\n";
        cout << "Gold Seats (" << goldCount << "): $" << goldCount * goldPrice << "\n";
        cout << "Silver Seats (" << silverCount << "): $" << silverCount * silverPrice << "\n";
        cout << "Total Amount: $" << totalAmount << "\n";
        cout << endl;

        bool isOnlineCustomer = false;
        PaymentDetails payment = getPaymentDetails(isOnlineCustomer, totalAmount);
        if (!processPayment(payment)) {
            cout << "Payment failed. Please try again.\n";
        }
        else {
            cout << "Booking confirmed! Enjoy your movie.\n";
        }
    }
    else if (choice == 2) {
        exitMessage();
    }
    else {
        cout << "Invalid choice. Please try again.\n";
        mainMenu();
    }
}