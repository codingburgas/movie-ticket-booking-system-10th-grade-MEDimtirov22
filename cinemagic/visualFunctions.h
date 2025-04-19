#pragma once
#ifndef VISUALFUNCTIONS_H
#define VISUALFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

void clearScreen();
void fullScreen();
void printLogo(const std::string& filename);
void paddingUp(int paddingSize);
int getConsoleWidth();
void centerText(std::string text);
void exitMessage();

#endif