#pragma once
#include <vector>
#include <string>

void adminMenu();

void loadData(
    std::vector<std::string>& cities,
    std::vector< std::vector<std::string> >& cinemas,
    std::vector<std::string>& genres,
    std::vector<std::string>& movieTitles,
    std::vector<std::string>& movieGenres
);

void saveData(
    std::vector<std::string>& cities,
    std::vector< std::vector<std::string> >& cinemas,
    std::vector<std::string>& genres,
    std::vector<std::string>& movieTitles,
    std::vector<std::string>& movieGenres
);