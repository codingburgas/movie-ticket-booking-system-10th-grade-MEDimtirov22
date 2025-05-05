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
    if (isOnlineCustomer) {
        std::cout << "1. Credit Card\n";
    }
    else {
        std::cout << "1. Credit Card\n";
        std::cout << "2. Cash\n";
    }
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

    if (choice == 1) {
        payment.method = CREDIT_CARD;
        while (true) {
            std::cout << "Enter your credit card number (16 digits): ";
            std::cin >> payment.cardNumber;

            if (validateCreditCard(payment.cardNumber)) {
                break;
            }
            else {
                std::cout << "Invalid credit card.\n";
            }
        }
    }
    else if (choice == 2 && !isOnlineCustomer) {
        payment.method = CASH;
    }

    payment.amount = totalAmount;
    return payment;
}