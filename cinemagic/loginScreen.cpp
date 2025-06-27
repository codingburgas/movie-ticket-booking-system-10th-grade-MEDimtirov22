#include "loginScreen.h"
#include "userManagement.h"
#include "loginValidation.h"
#include "visualFunctions.h"
#include "menu.h"
#include "admin.h"
#include "pch.h"

void signUp() {
    std::string username, password;
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        if (!isValidUsername(username)) {
            std::cout << "Invalid username. Must be at least 8 characters and contain only letters, digits, underscores, or periods.\n";
        }
        else {
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            if (!isValidPassword(password)) {
                std::cout << "Invalid password. Must be at least 8 characters and include uppercase, lowercase, digit, and special character.\n";
            }
            else {
                createNewUser(username, password);
                std::cout << "User registered successfully!\n";
                std::cout << "Press Enter to continue...";
                std::cin.get();
                return;
            }
        }

        while (true) {
            std::string choice;
            std::cout << "\nWould you like to try again? (y/n): ";
            std::getline(std::cin, choice);
            if (choice == "y" || choice == "Y") {
                break;
            }
            else if (choice == "n" || choice == "N") {
                return;
            }
            else {
                std::cout << "Please enter 'y' to try again or 'n' to return.\n";
            }
        }
    }
}

void logIn() {
    std::string username, password;
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        if (username.empty()) {
            std::cout << "Username cannot be empty.\n";
        }
        else {
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            if (password.empty()) {
                std::cout << "Password cannot be empty.\n";
            }
            else {
                if (findExistingUser(username, password)) {
                    mainMenu();
                    return;
                }
                else {
                    std::cout << "Invalid username or password.\n";
                }
            }
        }
        while (true) {
            std::string choice;
            std::cout << "\nWould you like to try again? (y/n): ";
            std::getline(std::cin, choice);
            if (choice == "y" || choice == "Y") {
                break;
            }
            else if (choice == "n" || choice == "N") {
                return;
            }
            else {
                std::cout << "Please enter 'y' to try again or 'n' to return.\n";
            }
        }
    }
}

void adminLogin() {
    std::string username, password;
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "Enter admin username: ";
        std::getline(std::cin, username);
        std::cout << "Enter admin password: ";
        std::getline(std::cin, password);

        if (username == "admin" && password == "admin") {
            adminMenu();
            return;
        }
        else {
            std::cout << "Invalid admin credentials.\n";
        }
        while (true) {
            std::string choice;
            std::cout << "\nWould you like to try again? (y/n): ";
            std::getline(std::cin, choice);
            if (choice == "y" || choice == "Y") {
                break;
            }
            else if (choice == "n" || choice == "N") {
                return;
            }
            else {
                std::cout << "Please enter 'y' to try again or 'n' to return.\n";
            }
        }
    }
}

void logInScreen() {
    while (true) {
        clearScreen();
        printLogo("logo.txt");
        std::cout << "1. Log In\n";
        std::cout << "2. Sign Up\n";
        std::cout << "3. Admin Login\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::string choice;
        std::getline(std::cin, choice);
        if (choice == "1") {
            logIn();
        }
        else if (choice == "2") {
            signUp();
        }
        else if (choice == "3") {
            adminLogin();
        }
        else if (choice == "4") {
            exitMessage();
            break;
        }
        else {
            clearScreen();
        }
    }
}