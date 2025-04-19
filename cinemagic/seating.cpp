#include "seating.h"
#include <iostream>
using namespace std;

void bookSeats(SeatingLayout& layout) {
    int numSeats;
    cout << "Enter number of seats to book: ";
    cin >> numSeats;

    for (int n = 0; n < numSeats; ++n) {
        int r, c;
        cout << "Enter seat (row and col, e.g., 0 2): ";
        cin >> r >> c;

        if (r >= 0 && r < layout.seats.size() &&
            c >= 0 && c < layout.seats[0].size()) {

            if (layout.seats[r][c].isBooked) {
                cout << "Seat already booked. Choose another.\n";
                n--; continue;
            }

            layout.seats[r][c].isBooked = true;
            cout << "Seat " << r << "," << c << " booked successfully.\n";
        }
        else {
            cout << "Invalid seat.\n";
            n--;
        }
    }
}


SeatingLayout createSampleLayout() {
    SeatingLayout layout;
    int rows = 5;
    int cols = 6;

    for (int i = 0; i < rows; i++) {
        vector<Seat> rowSeats;
        for (int j = 0; j < cols; j++) {
            Seat seat;
            seat.row = i;
            seat.col = j;
            seat.isBooked = false;

            // Simple logic: top rows are platinum, middle gold, bottom silver
            if (i < 1) seat.type = PLATINUM;
            else if (i < 3) seat.type = GOLD;
            else seat.type = SILVER;

            rowSeats.push_back(seat);
        }
        layout.seats.push_back(rowSeats);
    }

    return layout;
}

void displayLayout(const SeatingLayout& layout) {
    cout << "\nSeating Layout (X = Booked)\n";
    for (int i = 0; i < layout.seats.size(); i++) {
        for (int j = 0; j < layout.seats[i].size(); j++) {
            const Seat& seat = layout.seats[i][j];
            char symbol = seat.isBooked ? 'X' : 'O';

            switch (seat.type) {
            case SILVER: cout << "\033[37m"; break;
            case GOLD: cout << "\033[33m"; break;
            case PLATINUM: cout << "\033[36m"; break;
            }

            cout << symbol << " ";
        }
        cout << "\033[0m\n";
    }
    cout << "\033[0m\n"; // reset color
}
