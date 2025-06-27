#include "seating.h"
#include "visualFunctions.h"
#include "pch.h"

SeatingLayout SeatingManager::createSampleLayout() {
    SeatingLayout layout;

    int totalRows = 5;
    int totalColumns = 6;

    for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) {
        std::vector<Seat> currentRow;
        for (int colIndex = 0; colIndex < totalColumns; colIndex++) {
            Seat seat;
            seat.row = rowIndex;
            seat.col = colIndex;
            seat.isBooked = false;
            if (rowIndex == 0) {
                seat.type = PLATINUM;
            }
            else if (rowIndex < 3) {
                seat.type = GOLD;
            }
            else {
                seat.type = SILVER;
            }
            currentRow.push_back(seat);
        }
        layout.seats.push_back(currentRow);
    }
    return layout;
}

void SeatingManager::displayLayout(const SeatingLayout& layout) const {
    std::cout << "\nSeating Layout (X = Booked, O = Available)\n";
    for (int i = 0; i < layout.seats.size(); i++) {
        for (int j = 0; j < layout.seats[i].size(); j++) {
            const Seat& seat = layout.seats[i][j];
            char symbol = seat.isBooked ? 'X' : 'O';
            if (seat.type == SILVER) {
                std::cout << "\033[37m";
            }
            else if (seat.type == GOLD) {
                std::cout << "\033[33m";
            }
            else if (seat.type == PLATINUM) {
                std::cout << "\033[36m";
            }
            std::cout << symbol << " ";
        }
        std::cout << "\033[0m\n";
    }
    std::cout << "\033[0m\n";
}

bool SeatingManager::bookSeats(SeatingLayout& layout) {
    int seatsToBook = 0;
    std::cout << "Enter number of seats to book (0 to go back): ";
    std::cin >> seatsToBook;
    std::cin.ignore();
    if (seatsToBook == 0) {
        return false;
    }
    for (int booked = 0; booked < seatsToBook; booked++) {
        int row = -1, col = -1;
        std::cout << "Enter seat (row and col, e.g., 0 2): ";
        std::cin >> row >> col;
        std::cin.ignore();
        if (row >= 0 && row < layout.seats.size() && col >= 0 && col < layout.seats[0].size()) {
            if (layout.seats[row][col].isBooked) {
                std::cout << "Sorry, that seat is already booked. Please choose another.\n";
                booked--;
                continue;
            }
            layout.seats[row][col].isBooked = true;
            std::cout << "Seat " << row << "," << col << " booked successfully.\n";
        }
        else {
            std::cout << "Invalid seat position.\n";
            booked--;
        }
    }
    clearScreen();
    std::cout << "Seats booked successfully! Proceed to payment.\n";
    return true;
}