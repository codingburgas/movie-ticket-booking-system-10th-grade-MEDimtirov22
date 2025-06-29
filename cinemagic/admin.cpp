#include "admin.h"
#include "visualFunctions.h"
#include "pch.h"

int findString(std::vector<std::string>& v, std::string s) {
    int i;
    for (i = 0; i < (int)v.size(); i = i + 1) {
        if (v[i] == s) {
            return i;
        }
    }
    return -1;
}

void loadData(
    std::vector<std::string>& cities,
    std::vector<std::vector<std::string> >& cinemas,
    std::vector<std::string>& genres,
    std::vector<std::string>& movieTitles,
    std::vector<std::string>& movieGenres
) {
    cities.clear();
    cinemas.clear();
    genres.clear();
    movieTitles.clear();
    movieGenres.clear();

    std::ifstream file("data.txt");
    if (!file) {
        return;
    }

    std::string line;
    int section = 0;
    std::vector<std::string> cityNames;
    std::vector<std::vector<std::string> > cityCinemas;

    while (std::getline(file, line)) {
        if (line == "[Cities]") { 
            section = 1; 
            continue; 
        }
        if (line == "[Cinemas]") { 
            section = 2;
            continue; 
        }
        if (line == "[Genres]") { 
            section = 3;
            continue; 
        }
        if (line == "[Movies]") { 
            section = 4;
            continue; 
        }
        if (line == "") {
            continue;
        }

        if (section == 1) {
            cityNames.push_back(line);
        }
        else if (section == 2) {
            int bar = line.find('|');
            if (bar != -1) {
                std::string city = line.substr(0, bar);
                std::string cinema = line.substr(bar + 1);
                int cityPos = findString(cityNames, city);
                if (cityPos != -1) {
                    while ((int)cityCinemas.size() <= cityPos) {
                        cityCinemas.push_back(std::vector<std::string>());
                    }
                    cityCinemas[cityPos].push_back(cinema);
                }
            }
        }
        else if (section == 3) {
            genres.push_back(line);
        }
        else if (section == 4) {
            int bar = line.find('|');
            if (bar != -1) {
                movieTitles.push_back(line.substr(0, bar));
                movieGenres.push_back(line.substr(bar + 1));
            }
        }
    }
    cities = cityNames;
    cinemas = cityCinemas;
    while ((int)cinemas.size() < (int)cities.size()) {
        cinemas.push_back(std::vector<std::string>());
    }
    while ((int)cinemas.size() > (int)cities.size()) {
        cinemas.pop_back();
    }
}

void saveData(
    std::vector<std::string>& cities,
    std::vector<std::vector<std::string> >& cinemas,
    std::vector<std::string>& genres,
    std::vector<std::string>& movieTitles,
    std::vector<std::string>& movieGenres
) {
    while ((int)cinemas.size() < (int)cities.size()) {
        cinemas.push_back(std::vector<std::string>());
    }
    while ((int)cinemas.size() > (int)cities.size()) {
        cinemas.pop_back();
    }

    std::ofstream file("data.txt", std::ios::trunc);
    file << "[Cities]\n";
    int i;
    for (i = 0; i < (int)cities.size(); i = i + 1) {
        file << cities[i] << "\n";
    }
    file << "[Cinemas]\n";
    for (i = 0; i < (int)cities.size(); i = i + 1) {
        if ((int)cinemas.size() > i) {
            int j;
            for (j = 0; j < (int)cinemas[i].size(); j = j + 1) {
                file << cities[i] << "|" << cinemas[i][j] << "\n";
            }
        }
    }
    file << "[Genres]\n";
    for (i = 0; i < (int)genres.size(); i = i + 1) {
        file << genres[i] << "\n";
    }
    file << "[Movies]\n";
    for (i = 0; i < (int)movieTitles.size(); i = i + 1) {
        file << movieTitles[i] << "|" << movieGenres[i] << "\n";
    }
}

void adminAddMenu() {
    std::vector<std::string> cities, genres, movieTitles, movieGenres;
    std::vector<std::vector<std::string> > cinemas;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "1. Add City\n";
        std::cout << "2. Add Cinema\n";
        std::cout << "3. Add Genre\n";
        std::cout << "4. Add Movie\n";
        std::cout << "0. Back\n";
        std::cout << "Choose an option: ";
        std::string choice;
        std::getline(std::cin, choice);

        clearScreen();

        if (choice == "1") {
            std::cout << "Enter city name: ";
            std::string city;
            std::getline(std::cin, city);
            if (city != "" && findString(cities, city) == -1) {
                cities.push_back(city);
                cinemas.push_back(std::vector<std::string>());
                saveData(cities, cinemas, genres, movieTitles, movieGenres);
                std::cout << "City added.\n";
            }
            else {
                std::cout << "Invalid or duplicate name.\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        else if (choice == "2") {
            if (cities.size() == 0) {
                std::cout << "Add a city first.\nPress Enter...";
                std::cin.get();
                continue;
            }
            std::cout << "Select city:\n";
            int k;
            for (k = 0; k < (int)cities.size(); k = k + 1) {
                std::cout << k + 1 << ". " << cities[k] << "\n";
            }
            std::cout << "Choice: ";
            int cityNum;
            std::cin >> cityNum;
            std::cin.ignore();
            clearScreen();

            if (cityNum < 1 || cityNum >(int)cities.size()) {
                continue;
            }
            while ((int)cinemas.size() < (int)cities.size()) {
                cinemas.push_back(std::vector<std::string>());
            }
            while ((int)cinemas.size() > (int)cities.size()) {
                cinemas.pop_back();
            }
            std::cout << "Enter cinema name: ";
            std::string cinema;
            std::getline(std::cin, cinema);
            int cityIndex = cityNum - 1;
            if (cityIndex < 0 || cityIndex >= (int)cinemas.size()) {
                continue;
            }
            int already = findString(cinemas[cityIndex], cinema);
            if (cinema != "" && already == -1) {
                cinemas[cityIndex].push_back(cinema);
                saveData(cities, cinemas, genres, movieTitles, movieGenres);
                std::cout << "Cinema added.\n";
            }
            else {
                std::cout << "Invalid or duplicate name.\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        else if (choice == "3") {
            std::cout << "Enter genre name: ";
            std::string genre;
            std::getline(std::cin, genre);
            if (genre != "" && findString(genres, genre) == -1) {
                genres.push_back(genre);
                saveData(cities, cinemas, genres, movieTitles, movieGenres);
                std::cout << "Genre added.\n";
            }
            else {
                std::cout << "Invalid or duplicate name.\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        else if (choice == "4") {
            if (genres.size() == 0) {
                std::cout << "Add a genre first.\nPress Enter...";
                std::cin.get();
                continue;
            }
            std::cout << "Enter movie title: ";
            std::string title;
            std::getline(std::cin, title);
            int k;
            std::cout << "Select genre:\n";
            for (k = 0; k < (int)genres.size(); k = k + 1) {
                std::cout << k + 1 << ". " << genres[k] << "\n";
            }
            std::cout << "Choice: ";
            int genreNum;
            std::cin >> genreNum;
            std::cin.ignore();
            clearScreen();
            if (genreNum < 1 || genreNum >(int)genres.size()) {
                continue;
            }
            if (title != "") {
                movieTitles.push_back(title);
                movieGenres.push_back(genres[genreNum - 1]);
                saveData(cities, cinemas, genres, movieTitles, movieGenres);
                std::cout << "Movie added.\n";
            }
            else {
                std::cout << "Invalid title.\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        else if (choice == "0") {
            break;
        }
        else {
            continue;
        }
    }
}

void adminDeleteMenu() {
    std::vector<std::string> cities, genres, movieTitles, movieGenres;
    std::vector<std::vector<std::string> > cinemas;
    loadData(cities, cinemas, genres, movieTitles, movieGenres);

    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "1. Delete City\n";
        std::cout << "2. Delete Cinema\n";
        std::cout << "3. Delete Genre\n";
        std::cout << "4. Delete Movie\n";
        std::cout << "0. Back\n";
        std::cout << "Choose an option: ";
        std::string choice;
        std::getline(std::cin, choice);

        clearScreen();

        if (choice == "1") {
            if (cities.size() == 0) {
                std::cout << "No cities.\n";
                std::cin.get();
                continue;
            }
            int k;
            for (k = 0; k < (int)cities.size(); k = k + 1) {
                std::cout << k + 1 << ". " << cities[k] << "\n";
            }
            std::cout << "Number to delete: ";
            int cityNum;
            std::cin >> cityNum;
            std::cin.ignore();
            clearScreen();

            if (cityNum < 1 || cityNum >(int)cities.size()) {
                continue;
            }
            cities.erase(cities.begin() + cityNum - 1);
            cinemas.erase(cinemas.begin() + cityNum - 1);
            while ((int)cinemas.size() < (int)cities.size()) {
                cinemas.push_back(std::vector<std::string>());
            }
            while ((int)cinemas.size() > (int)cities.size()) {
                cinemas.pop_back();
            }
            saveData(cities, cinemas, genres, movieTitles, movieGenres);
            std::cout << "City deleted.\nPress Enter...";
            std::cin.get();
        }
        else if (choice == "2") {
            if (cities.size() == 0) {
                std::cout << "No cities.\n";
                std::cin.get();
                continue;
            }
            int k;
            for (k = 0; k < (int)cities.size(); k = k + 1) {
                std::cout << k + 1 << ". " << cities[k] << "\n";
            }
            std::cout << "Select city: ";
            int cityNum;
            std::cin >> cityNum;
            std::cin.ignore();
            clearScreen();
            if (cityNum < 1 || cityNum >(int)cities.size()) {
                continue;
            }
            while ((int)cinemas.size() < (int)cities.size()) {
                cinemas.push_back(std::vector<std::string>());
            }
            while ((int)cinemas.size() > (int)cities.size()) {
                cinemas.pop_back();
            }
            if (cinemas[cityNum - 1].size() == 0) {
                std::cout << "No cinemas for this city.\n";
                std::cin.get();
                continue;
            }
            for (k = 0; k < (int)cinemas[cityNum - 1].size(); k = k + 1) {
                std::cout << k + 1 << ". " << cinemas[cityNum - 1][k] << "\n";
            }
            std::cout << "Number to delete: ";
            int cinemaNum;
            std::cin >> cinemaNum;
            std::cin.ignore();
            clearScreen();
            if (cinemaNum < 1 || cinemaNum >(int)cinemas[cityNum - 1].size()) {
                continue;
            }
            cinemas[cityNum - 1].erase(cinemas[cityNum - 1].begin() + cinemaNum - 1);
            saveData(cities, cinemas, genres, movieTitles, movieGenres);
            std::cout << "Cinema deleted.\nPress Enter...";
            std::cin.get();
        }
        else if (choice == "3") {
            if (genres.size() == 0) {
                std::cout << "No genres.\n";
                std::cin.get();
                continue;
            }
            int k;
            for (k = 0; k < (int)genres.size(); k = k + 1) {
                std::cout << k + 1 << ". " << genres[k] << "\n";
            }
            std::cout << "Number to delete: ";
            int genreNum;
            std::cin >> genreNum;
            std::cin.ignore();
            clearScreen();
            if (genreNum < 1 || genreNum >(int)genres.size()) {
                continue;
            }
            std::string delGenre = genres[genreNum - 1];
            genres.erase(genres.begin() + genreNum - 1);
            int m = 0;
            while (m < (int)movieGenres.size()) {
                if (movieGenres[m] == delGenre) {
                    movieGenres.erase(movieGenres.begin() + m);
                    movieTitles.erase(movieTitles.begin() + m);
                }
                else {
                    m = m + 1;
                }
            }
            saveData(cities, cinemas, genres, movieTitles, movieGenres);
            std::cout << "Genre (and its movies) deleted.\nPress Enter...";
            std::cin.get();
        }
        else if (choice == "4") {
            if (movieTitles.size() == 0) {
                std::cout << "No movies.\n";
                std::cin.get();
                continue;
            }
            int k;
            for (k = 0; k < (int)movieTitles.size(); k = k + 1) {
                std::cout << k + 1 << ". " << movieTitles[k] << " (" << movieGenres[k] << ")\n";
            }
            std::cout << "Number to delete: ";
            int movieNum;
            std::cin >> movieNum;
            std::cin.ignore();
            clearScreen();
            if (movieNum < 1 || movieNum >(int)movieTitles.size()) {
                continue;
            }
            movieTitles.erase(movieTitles.begin() + movieNum - 1);
            movieGenres.erase(movieGenres.begin() + movieNum - 1);
            saveData(cities, cinemas, genres, movieTitles, movieGenres);
            std::cout << "Movie deleted.\nPress Enter...";
            std::cin.get();
        }
        else if (choice == "0") {
            break;
        }
        else {
            clearScreen();
            continue;
        }
    }
}

void adminMenu() {
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "1. Add\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Log Out\n";
        std::cout << "Choose an option: ";
        std::string choice;
        std::getline(std::cin, choice);

        clearScreen();

        if (choice == "1") {
            adminAddMenu();
        }
        else if (choice == "2") {
            adminDeleteMenu();
        }
        else if (choice == "3") {
            break;
        }
        else {
            clearScreen();
            continue;
        }
    }
}