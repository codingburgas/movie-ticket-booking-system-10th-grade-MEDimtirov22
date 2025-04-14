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

#endif