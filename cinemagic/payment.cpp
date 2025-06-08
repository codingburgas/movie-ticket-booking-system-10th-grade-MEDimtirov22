#include "payment.h"
#include "visualFunctions.h"
#include "pch.h"

// Luhn algorithm
bool validateCreditCard(const std::string& cardNumber) {
    int nDigits = cardNumber.length();
    int sum = 0;
    bool isSecond = false;

    for (int i = nDigits - 1; i >= 0; i--) {
        int digit = cardNumber[i] - '0';
        if (isSecond) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        isSecond = !isSecond;
    }
    return (sum % 10 == 0);
}

bool processPayment(const PaymentDetails& payment) {
    if (payment.method == CREDIT_CARD) {
        std::cout << "Processing credit card payment...\n";
        std::cout << "Card Number: " << payment.cardNumber << std::endl;
    }
    else if (payment.method == CASH) {
        std::cout << "Processing cash payment...\n";
        std::cout << "Please submit $" << std::fixed << std::setprecision(2) << payment.amount << " to the cashier.\n";
    }
    std::cout << "Payment of $" << std::fixed << std::setprecision(2) << payment.amount << " successful!\n";
    return true;
}

void displayPaymentOptions(bool isOnlineCustomer) {
    std::cout << "Payment Options:\n";
    std::cout << "1. Credit Card\n";
    if (!isOnlineCustomer) {
        std::cout << "2. Cash\n";
    }
}

std::string removeSpaces(const std::string& input) {
    std::string result;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] != ' ') {
            result += input[i];
        }
    }
    return result;
}

bool isAllDigits(const std::string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        if (!std::isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

PaymentDetails getPaymentDetails(bool isOnlineCustomer, double totalAmount) {
    PaymentDetails payment;
    int choice;

    while (true) {
        displayPaymentOptions(isOnlineCustomer);
        std::cout << "Select a payment method: ";
        std::cin >> choice;

        if (isOnlineCustomer && choice != 1) {
            std::cout << "Invalid choice for online payment. Please select Credit Card.\n";
        }
        else if (!isOnlineCustomer && (choice < 1 || choice > 2)) {
            std::cout << "Invalid choice. Please choose a valid payment method.\n";
        }
        else {
            break;
        }
    }

    while (true) {
        if (choice == 1) {
            payment.method = CREDIT_CARD;

            std::string rawInput;
            std::cout << "Enter your credit card number (16 digits) or 0 to go back: ";
            std::cin >> rawInput;

            if (rawInput == "0") {
                return getPaymentDetails(isOnlineCustomer, totalAmount);
            }

            std::string cardNumber = removeSpaces(rawInput);

            if (cardNumber.length() != 16 || !isAllDigits(cardNumber)) {
                std::cout << "Invalid credit card.\n";
                continue;
            }
            if (!validateCreditCard(cardNumber)) {
                std::cout << "Invalid credit card.\n";
                continue;
            }
            payment.cardNumber = cardNumber;
            break;
        }
        else if (choice == 2 && !isOnlineCustomer) {
            payment.method = CASH;
            break;
        }
    }

    payment.amount = totalAmount;
    return payment;
}