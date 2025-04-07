#pragma once
#include "pch.h"

void clearScreen();

void fullScreen();

void paddingUp(int paddingSize);

void printLogo(const std::string& filename);

int getConsoleWidth();

void exitMessage();

void centerText(std::string text);