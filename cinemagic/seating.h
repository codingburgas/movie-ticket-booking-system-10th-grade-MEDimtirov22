#pragma once
#include "structs.h"
#include <vector>

class SeatingManager {
public:
    SeatingLayout createSampleLayout();
    void displayLayout(const SeatingLayout& layout) const;
    void bookSeats(SeatingLayout& layout);
};