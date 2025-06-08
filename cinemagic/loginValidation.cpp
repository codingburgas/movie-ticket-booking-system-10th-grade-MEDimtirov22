#include "loginValidation.h"

bool isAlnum(char ch) {
    return (ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z') ||
        (ch >= '0' && ch <= '9');
}

bool isUpper(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

bool isLower(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isValidUsername(const std::string& username) {

    for (char ch : username) {
        if (!isAlnum(ch) && ch != '_' && ch != '.') {
            return false;
        }
    }
    return true;
}

bool isValidPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char ch : password) {
        if (isUpper(ch)) {
            hasUpper = true;
        }
        else if (isLower(ch)) {
            hasLower = true;
        }
        else if (isDigit(ch)) {
            hasDigit = true;
        }
        else {
            hasSpecial = true;
        }
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
