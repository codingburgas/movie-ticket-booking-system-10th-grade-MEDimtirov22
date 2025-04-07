#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
using namespace std;

struct Cinema {
    string name;
};

struct City {
    string name;
    Cinema cinemas[2];
};

struct Movie {
    string title;
    string genre;
};

#endif