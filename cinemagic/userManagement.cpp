#include "userManagement.h"
#include "pch.h"

void createNewUser(const std::string& username, const std::string& password) {
    std::ofstream file("users.csv", std::ios::app);
    if (file.is_open()) {
        file << username << "," << password << "\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open users.csv for writing.\n";
    }
}

bool findExistingUser(const std::string& username, const std::string& password) {
    std::ifstream file("users.csv");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedUsername, storedPassword;
        if (std::getline(iss, storedUsername, ',') && std::getline(iss, storedPassword)) {
            if (storedUsername == username && storedPassword == password) {
                return true;
            }
        }
    }
    return false;
}

bool fullValidation(const std::string& username, const std::string& password) {
    std::ifstream file("users.csv");
    std::string line;
    while (std::getline(file, line)) {
        size_t comma = line.find(',');
        std::string fileUser = line.substr(0, comma);
        std::string filePass = line.substr(comma + 1);
        if (fileUser == username && filePass == password)
            return true;
    }
    return false;
}

bool findUsername(const std::string& username) {
    std::ifstream file("users.csv");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, line.find(',')) == username)
            return true;
    }
    return false;
}