#pragma once
#include <string>

void createNewUser(const std::string& username, const std::string& password);
bool findExistingUser(const std::string& username, const std::string& password);

bool fullValidation(const std::string& username, const std::string& password);
bool findUsername(const std::string& username);