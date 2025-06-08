#include "functions.h"
#include "data.h"
#include "visualFunctions.h"
#include "payment.h"
#include "pch.h"

int BookingSystem::selectCity() {
    int cityChoice;
    while (true) {
        clearScreen();
        std::cout << "Please select a city:\n";
        for (int i = 0; i < NUM_CITIES; ++i) {
            std::cout << i + 1 << ". " << cities[i].name << std::endl;
        }
        std::cout << "0. Back\n";
        std::cout << "Choice (0-" << NUM_CITIES << "): ";
        std::cin >> cityChoice;
        if (cityChoice == 0) {
            return -1;
        }
        if (cityChoice >= 1 && cityChoice <= NUM_CITIES) {
            return cityChoice;
        }
        clearScreen();
    }
}

int BookingSystem::selectCinema(int cityChoice) {
    int cinemaChoice;
    clearScreen();
    std::cout << "Please select a cinema: \n";
    int cinemaCount = cities[cityChoice - 1].cinemas.size();
    for (int i = 0; i < cinemaCount; ++i) {
        std::cout << i + 1 << ". " << cities[cityChoice - 1].cinemas[i].name << std::endl;
    }
    std::cout << "0. Back\n";
    while (true) {
        std::cout << "Choice (0-" << cinemaCount << "): ";
        std::cin >> cinemaChoice;
        if (cinemaChoice == 0) {
            return -1;
        }
        if (cinemaChoice >= 1 && cinemaChoice <= cinemaCount) {
            return cinemaChoice;
        }
        clearScreen();
    }
}

int BookingSystem::selectGenre() {
    int genreChoice;
    clearScreen();
    std::cout << "Please select a genre:\n";
    for (int i = 0; i < NUM_GENRES; ++i) {
        std::cout << i + 1 << ". " << genres[i] << std::endl;
    }
    std::cout << "0. Back\n";
    while (true) {
        std::cout << "Choice (0-" << NUM_GENRES << "): ";
        std::cin >> genreChoice;
        if (genreChoice == 0) {
            return -1;
        }
        if (genreChoice >= 1 && genreChoice <= NUM_GENRES) {
            return genreChoice;
        }
        clearScreen();
    }
}

int BookingSystem::selectMovie(int genreChoice) {
    int movieChoice;
    clearScreen();
    std::cout << "Available movies in " << genres[genreChoice - 1] << " genre:\n";
    std::vector<int> filteredMovieIndices;
    int filteredIndex = 1;
    for (int i = 0; i < NUM_MOVIES; ++i) {
        if (movies[i].genre == genres[genreChoice - 1]) {
            std::cout << filteredIndex << ". " << movies[i].title << std::endl;
            filteredMovieIndices.push_back(i);
            ++filteredIndex;
        }
    }
    std::cout << "0. Back\n";
    while (true) {
        std::cout << "Please select a movie:\n";
        std::cin >> movieChoice;
        if (movieChoice == 0) {
            return -1;
        }
        if (movieChoice >= 1 && movieChoice <= filteredMovieIndices.size()) {
            return filteredMovieIndices[movieChoice - 1];
        }
        clearScreen();
    }
}

double BookingSystem::calculateTotalPrice(const std::vector<Seat>& selectedSeats) {
    double total = 0.0;
    for (const Seat& seat : selectedSeats) {
        switch (seat.type) {
        case PLATINUM:
            total += 20.0;
            break;
        case GOLD:     
            total += 15.0; 
            break;
        case SILVER:  
            total += 10.0;
            break;
        }
    }
    return total;
}

void BookingSystem::completeBooking(int cityChoice, int cinemaChoice, int movieChoice, const std::vector<Seat>& selectedSeats, bool isOnlineCustomer) {
    double totalPrice = calculateTotalPrice(selectedSeats);
    std::cout << "Total Price: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    PaymentDetails payment = getPaymentDetails(isOnlineCustomer, totalPrice);
    if (processPayment(payment)) {
        std::cout << "Booking confirmed!\nEnjoy your movie!\n";
        _getch();
    }
    else {
        std::cout << "Payment failed. Booking not confirmed.\n";
    }
}

void BookingSystem::printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice) {
    clearScreen();
    std::cout << "Booking successful, you have selected:\n";
    std::cout << "City: " << cities[cityChoice - 1].name << std::endl;
    std::cout << "Cinema: " << cities[cityChoice - 1].cinemas[cinemaChoice - 1].name << std::endl;
    std::cout << "Movie: " << movies[movieChoice].title << std::endl;
}