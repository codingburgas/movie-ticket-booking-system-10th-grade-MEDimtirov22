#include "pch.h"
#include "functions.h"
#include "data.h"
#include "visualFunctions.h"
#include "functions.h"
#include "payment.h"

using namespace std;

int selectCity() {
    int cityChoice;
    while (true) {
        clearScreen();
        cout << "Please select a city:\n";
        for (int i = 0; i < NUM_CITIES; ++i) {
            cout << i + 1 << ". " << cities[i].name << endl;
        }

        cout << "Choice (1-" << NUM_CITIES << "): ";
        cin >> cityChoice;

        if (cityChoice >= 1 && cityChoice <= NUM_CITIES) {
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid city.\n";
        }
    }
    return cityChoice;
}

int selectCinema(int cityChoice) {
    int cinemaChoice;
    clearScreen();
    cout << "You selected " << cities[cityChoice - 1].name << ". Please select a cinema:\n";
    int cinemaCount = cities[cityChoice - 1].cinemas.size();
    for (int i = 0; i < cinemaCount; ++i) {
        cout << i + 1 << ". " << cities[cityChoice - 1].cinemas[i].name << endl;
    }

    while (true) {
        cout << "Choice (1-" << cinemaCount << "): ";
        cin >> cinemaChoice;

        if (cinemaChoice >= 1 && cinemaChoice <= cinemaCount) {
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid cinema.\n";
        }
    }
    return cinemaChoice;
}

int selectGenre() {
    int genreChoice;
    clearScreen();
    cout << "Please select a genre:\n";
    for (int i = 0; i < NUM_GENRES; ++i) {
        cout << i + 1 << ". " << genres[i] << endl;
    }

    while (true) {
        cout << "Choice (1-" << NUM_GENRES << "): ";
        cin >> genreChoice;

        if (genreChoice >= 1 && genreChoice <= NUM_GENRES) {
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid genre.\n";
        }
    }
    return genreChoice;
}

int selectMovie(int genreChoice) {
    int movieChoice;
    clearScreen();
    cout << "Available movies in " << genres[genreChoice - 1] << " genre:\n";

    vector<int> filteredMovieIndices;
    int filteredIndex = 1;

    for (int i = 0; i < NUM_MOVIES; ++i) {
        if (movies[i].genre == genres[genreChoice - 1]) {
            cout << filteredIndex << ". " << movies[i].title << endl;
            filteredMovieIndices.push_back(i);
            ++filteredIndex;
        }
    }

    while (true) {
        cout << "Enter your choice of movie: ";
        cin >> movieChoice;

        if (movieChoice >= 1 && movieChoice <= filteredMovieIndices.size()) {
            return filteredMovieIndices[movieChoice - 1];
        }
        else {
            cout << "Invalid choice. Please select a valid movie.\n";
        }
    }
}

double calculateTotalPrice(const vector<Seat>& selectedSeats) {
    double total = 0.0;
    for (const Seat& seat : selectedSeats) {
        switch (seat.type) {
        case PLATINUM: total += 20.0; break;
        case GOLD: total += 15.0; break;
        case SILVER: total += 10.0; break;
        }
    }
    return total;
}

void completeBooking(int cityChoice, int cinemaChoice, int movieChoice, const vector<Seat>& selectedSeats, bool isOnlineCustomer) {
    double totalPrice = calculateTotalPrice(selectedSeats);

    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;

    PaymentDetails payment = getPaymentDetails(isOnlineCustomer, totalPrice);

    if (processPayment(payment)) {
        cout << "Booking confirmed!\n";
        cout << "Enjoy your movie!\n";
    }
    else {
        cout << "Payment failed. Booking not confirmed.\n";
    }
}
void printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice) {
    clearScreen();
    cout << "Booking successful, you have selected:" << endl;
    cout << "City: " << cities[cityChoice - 1].name << endl;
    cout << "Cinema: " << cities[cityChoice - 1].cinemas[cinemaChoice - 1].name << endl;
    cout << "Movie: " << movies[movieChoice].title << endl;
}