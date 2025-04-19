#pragma once
#ifndef SEATING_H
#define SEATING_H

#include "structs.h"

SeatingLayout createSampleLayout();
void displayLayout(const SeatingLayout& layout);
void bookSeats(SeatingLayout& layout);

#endif
