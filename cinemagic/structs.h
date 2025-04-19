#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
using namespace std;

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

enum SeatType { SILVER, GOLD, PLATINUM };

struct Seat {
    int row;
    int col;
    SeatType type;
    bool isBooked;
};

struct SeatingLayout {
    vector<vector<Seat>> seats;
};

#endif