#include "functions.h"
#include "visualFunctions.h"
#include "payment.h"
#include "admin.h"
#include "pch.h"

int BookingSystem::selectCity() {
    std::vector<std::string> cities;
    std::vector<std::vector<std::string>> cinemas;
    std::vector<std::string> genres;
    std::vector<std::string> movieTitles;
    std::vector<std::string> movieGenres;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    if (cities.empty()) {
        clearScreen();
        std::cout << "No cities available. Please ask admin to add some.\n";
        std::cout << "0. Back\nChoice (0): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        return -1;
    }

    int cityChoice;
    while (true) {
        clearScreen();
        std::cout << "Please select a city:\n";
        for (size_t i = 0; i < cities.size(); ++i) {
            std::cout << i + 1 << ". " << cities[i] << std::endl;
        }
        std::cout << "0. Back\nChoice (0-" << cities.size() << "): ";
        std::cin >> cityChoice;
        std::cin.ignore();
        if (cityChoice == 0) {
            return -1;
        }
        if (cityChoice >= 1 && (size_t)cityChoice <= cities.size()) {
            return cityChoice;
        }
        clearScreen();
    }
}

int BookingSystem::selectCinema(int cityChoice) {
    std::vector<std::string> cities;
    std::vector<std::vector<std::string>> cinemas;
    std::vector<std::string> genres;
    std::vector<std::string> movieTitles;
    std::vector<std::string> movieGenres;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    if (cityChoice < 1 || (size_t)cityChoice > cinemas.size() || cinemas[cityChoice - 1].empty()) {
        clearScreen();
        std::cout << "No cinemas available for this city.\n";
        std::cout << "0. Back\nChoice (0): ";
        int cinemaChoice;
        std::cin >> cinemaChoice;
        std::cin.ignore();
        return -1;
    }

    const std::vector<std::string>& cinemaList = cinemas[cityChoice - 1];
    int cinemaCount = cinemaList.size();

    int cinemaChoice;
    while (true) {
        clearScreen();
        std::cout << "Please select a cinema: \n";
        for (int i = 0; i < cinemaCount; ++i) {
            std::cout << i + 1 << ". " << cinemaList[i] << std::endl;
        }
        std::cout << "0. Back\nChoice (0-" << cinemaCount << "): ";
        std::cin >> cinemaChoice;
        std::cin.ignore();
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
    std::vector<std::string> cities;
    std::vector<std::vector<std::string>> cinemas;
    std::vector<std::string> genres;
    std::vector<std::string> movieTitles;
    std::vector<std::string> movieGenres;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    if (genres.empty()) {
        clearScreen();
        std::cout << "No genres available.\n";
        std::cout << "0. Back\nChoice (0): ";
        int genreChoice;
        std::cin >> genreChoice;
        std::cin.ignore();
        return -1;
    }

    int genreChoice;
    while (true) {
        clearScreen();
        std::cout << "Please select a genre:\n";
        for (size_t i = 0; i < genres.size(); ++i) {
            std::cout << i + 1 << ". " << genres[i] << std::endl;
        }
        std::cout << "0. Back\nChoice (0-" << genres.size() << "): ";
        std::cin >> genreChoice;
        std::cin.ignore();
        if (genreChoice == 0) {
            return -1;
        }
        if (genreChoice >= 1 && (size_t)genreChoice <= genres.size()) {
            return genreChoice;
        }
        clearScreen();
    }
}

int BookingSystem::selectMovie(int genreChoice) {
    std::vector<std::string> cities;
    std::vector<std::vector<std::string>> cinemas;
    std::vector<std::string> genres;
    std::vector<std::string> movieTitles;
    std::vector<std::string> movieGenres;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    if (genreChoice < 1 || (size_t)genreChoice > genres.size()) {
        return -1;
    }

    while (true) {
        clearScreen();
        std::cout << "Available movies in " << genres[genreChoice - 1] << " genre:\n";
        std::vector<int> filteredMovieIndices;
        int filteredIndex = 1;
        for (size_t i = 0; i < movieTitles.size(); ++i) {
            if (movieGenres[i] == genres[genreChoice - 1]) {
                std::cout << filteredIndex << ". " << movieTitles[i] << std::endl;
                filteredMovieIndices.push_back(i);
                ++filteredIndex;
            }
        }
        if (filteredMovieIndices.empty()) {
            std::cout << "No movies available in this genre.\n";
            std::cout << "0. Back\nChoice (0): ";
            int movieChoice;
            std::cin >> movieChoice;
            std::cin.ignore();
            return -1;
        }

        std::cout << "0. Back\nChoice (0-" << filteredMovieIndices.size() << "): ";
        int movieChoice;
        std::cin >> movieChoice;
        std::cin.ignore();
        if (movieChoice == 0) {
            return -1;
        }
        if (movieChoice >= 1 && (size_t)movieChoice <= filteredMovieIndices.size()) {
            return filteredMovieIndices[movieChoice - 1];
        }
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
        saveBookingCSV(cityChoice, cinemaChoice, movieChoice, selectedSeats);
        _getch();
    }
    else {
        std::cout << "Payment failed. Booking not confirmed.\n";
    }
}

void BookingSystem::printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice) {
    std::vector<std::string> cities;
    std::vector<std::vector<std::string>> cinemas;
    std::vector<std::string> genres;
    std::vector<std::string> movieTitles;
    std::vector<std::string> movieGenres;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    clearScreen();
    std::cout << "Booking successful, you have selected:\n";
    std::cout << "City: " << cities[cityChoice - 1] << std::endl;
    std::cout << "Cinema: " << cinemas[cityChoice - 1][cinemaChoice - 1] << std::endl;
    std::cout << "Movie: " << movieTitles[movieChoice] << std::endl;
}

void BookingSystem::saveBookingCSV(int cityChoice, int cinemaChoice, int movieChoice, const std::vector<Seat>& selectedSeats) {
    std::ofstream file("bookings.csv", std::ios::app);
    if (!file.is_open()) {
        return;
    }

    for (int i = 0; i < (int)selectedSeats.size(); i++) {
        file << cityChoice << "," << cinemaChoice << "," << movieChoice << "," << selectedSeats[i].row << "," << selectedSeats[i].col << "\n";
    }

    file.close();
}

std::vector<Seat> BookingSystem::loadBookedSeatsCSV(int cityChoice, int cinemaChoice, int movieChoice) {
    std::vector<Seat> bookedSeats;
    std::ifstream file("bookings.csv");
    if (!file.is_open()) {
        return bookedSeats;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int city, cinema, movie, row, col;
        char sep;
        if ((iss >> city >> sep >> cinema >> sep >> movie >> sep >> row >> sep >> col)
            && (city == cityChoice && cinema == cinemaChoice && movie == movieChoice)) {
            Seat seat;
            seat.row = row;
            seat.col = col;
            seat.isBooked = true;
            bookedSeats.push_back(seat);
        }
    }
    file.close();
    return bookedSeats;
}