#pragma once

#include <string>
#include <vector>
using namespace std;

enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

inline string seatTypeToString(SeatType type) {
    switch (type) {
    case SeatType::SILVER: return "SILVER";
    case SeatType::GOLD: return "GOLD";
    case SeatType::PLATINUM: return "PLATINUM";
    default: return "UNKNOWN";
    }
}

struct Cinema {
    string name;
};

struct City {
    string name;
    vector<Cinema> cinemas;
};

struct Movie {
    string title;
    string genre;
};

struct Seat {
    int row;
    int col;
    SeatType type;
    bool isBooked;
};

struct SeatingLayout {
    vector<vector<Seat>> seats;
};
