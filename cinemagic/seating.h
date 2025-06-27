#pragma once
#include "structs.h"
#include <vector>

class SeatingManager {
public:
    SeatingLayout createSampleLayout();
    void displayLayout(const SeatingLayout& layout) const;
    bool bookSeats(SeatingLayout& layout);
};