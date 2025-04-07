#include "./visualFunctions.h"

using namespace std;

struct Cinema {
    string name;
};

struct City {
    string name;
    Cinema cinemas[2];
};

struct Movie {
    string title;
    string genre;
};

int main() {
    City cities[] = {
        {"New York", {{"AMC Empire 25"}, {"Regal E-Walk"}}},
        {"Los Angeles", {{"TCL Chinese Theatre"}, {"AMC Sunset 5"}}},
        {"Chicago", {{"AMC River East 21"}, {"Landmark's Century Centre"}}}
    };

    Movie movies[] = {
        {"The Batman", "Action"},
        {"Avatar 2", "Adventure"},
        {"Spider-Man: No Way Home", "Action"},
        {"The Notebook", "Romance"},
        {"Inside Out", "Animation"},
        {"Get Out", "Horror"}
    };

    string genres[] = { "Action", "Adventure", "Romance", "Animation", "Horror" };
    int cityChoice, cinemaChoice, genreChoice, movieChoice;

    cout << "Welcome to the Movie Ticket Booking System!\n";

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

    clearScreen();
    cout << "Available movies in " << genres[genreChoice - 1] << " genre:\n";
    for (int i = 0; i < 6; ++i) {
        if (movies[i].genre == genres[genreChoice - 1]) {
            cout << i + 1 << ". " << movies[i].title << endl;
        }
    }

    while (true) {
        cout << "Enter your choice of movie: ";
        cin >> movieChoice;

        if (movieChoice >= 1 && movieChoice <= 6 && movies[movieChoice - 1].genre == genres[genreChoice - 1]) {
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid movie.\n";
        }
    }

    clearScreen();
    cout << "Booking successful, you have selected:" << endl;
    cout << "City: " << cities[cityChoice - 1].name << endl;
    cout << "Cinema: " << cities[cityChoice - 1].cinemas[cinemaChoice - 1].name << endl;
    cout << "Movie: " << movies[movieChoice - 1].title << endl;
}