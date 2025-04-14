#include <iostream>
#include <vector>
#include "functions.h"
#include "data.h"
#include "visualFunctions.h"

using namespace std;

int selectCity() {
    int cityChoice;
    while (true) {
        clearScreen();
        cout << "Please select a city:\n";
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << ". " << cities[i].name << endl;
        }

        cout << "Choice (1-3): ";
        cin >> cityChoice;

        if (cityChoice >= 1 && cityChoice <= 3) {
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
    for (int i = 0; i < 2; ++i) {
        cout << i + 1 << ". " << cities[cityChoice - 1].cinemas[i].name << endl;
    }

    while (true) {
        cout << "Choice (1-2): ";
        cin >> cinemaChoice;

        if (cinemaChoice >= 1 && cinemaChoice <= 2) {
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
    for (int i = 0; i < 5; ++i) {
        cout << i + 1 << ". " << genres[i] << endl;
    }

    while (true) {
        cout << "Choice (1-5): ";
        cin >> genreChoice;

        if (genreChoice >= 1 && genreChoice <= 5) {
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

    for (int i = 0; i < 6; ++i) {
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

void printBookingDetails(int cityChoice, int cinemaChoice, int movieChoice) {
    clearScreen();
    cout << "Booking successful, you have selected:" << endl;
    cout << "City: " << cities[cityChoice - 1].name << endl;
    cout << "Cinema: " << cities[cityChoice - 1].cinemas[cinemaChoice - 1].name << endl;
    cout << "Movie: " << movies[movieChoice - 1].title << endl;
}