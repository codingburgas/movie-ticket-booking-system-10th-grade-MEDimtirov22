#include "seating.h"
#include "visualFunctions.h"
#include "pch.h"

void bookSeats(SeatingLayout& layout) {
    int numSeats;
    std::cout << "Enter number of seats to book: ";
    std::cin >> numSeats;

    for (int n = 0; n < numSeats; ++n) {
        int r, c;
        std::cout << "Enter seat (row and col, e.g., 0 2): ";
        std::cin >> r >> c;

        if (r >= 0 && r < layout.seats.size() &&
            c >= 0 && c < layout.seats[0].size()) {

            if (layout.seats[r][c].isBooked) {
                std::cout << "Seat already booked. Choose another.\n";
                n--; 
                continue;
            }

            layout.seats[r][c].isBooked = true;
            std::cout << "Seat " << r << "," << c << " booked successfully.\n";
        }
        else {
            std::cout << "Invalid seat.\n";
            n--;
        }
    }
}

SeatingLayout createSampleLayout() {
    SeatingLayout layout;
    int rows = 5;
    int cols = 6;

    for (int i = 0; i < rows; i++) {
        std::vector<Seat> rowSeats;
        for (int j = 0; j < cols; j++) {
            Seat seat;
            seat.row = i;
            seat.col = j;
            seat.isBooked = false;

            if (i < 1) {
                seat.type = PLATINUM;
            }
            else if (i < 3) {
                seat.type = GOLD;
            }
            else {
                seat.type = SILVER;
            }

            rowSeats.push_back(seat);
        }
        layout.seats.push_back(rowSeats);
    }

    return layout;
}

void displayLayout(const SeatingLayout& layout) {
    std::cout << "\nSeating Layout (X = Booked)\n";
    for (int i = 0; i < layout.seats.size(); i++) {
        for (int j = 0; j < layout.seats[i].size(); j++) {
            const Seat& seat = layout.seats[i][j];
            char symbol;
            if (seat.isBooked) {
                symbol = 'X';
            }
            else {
                symbol = 'O';
            }

            switch (seat.type) {
            case SILVER:
                std::cout << "\033[37m";
                break;
            case GOLD:
                std::cout << "\033[33m";
                break;
            case PLATINUM:
                std::cout << "\033[36m";
                break;
            }

            std::cout << symbol << " ";
        }
        std::cout << "\033[0m\n";
    }
    std::cout << "\033[0m\n";
}
