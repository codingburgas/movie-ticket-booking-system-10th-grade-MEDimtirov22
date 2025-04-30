#include "payment.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Luhn algorithm
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

void displayPaymentError(const std::string& errorMessage) {
    cout << "Payment Error: " << errorMessage << endl;
}

bool processPayment(const PaymentDetails& payment) {
    if (payment.method == CREDIT_CARD) {
        cout << "Processing credit card payment...\n";
        cout << "Card Number: " << payment.cardNumber << endl;
    }
    else if (payment.method == CASH) {
        cout << "Processing cash payment...\n";
        cout << "Please submit $" << fixed << setprecision(2) << payment.amount << " to the cashier.\n";
    }

    cout << "Payment of $" << fixed << setprecision(2) << payment.amount << " successful!\n";
    return true;
}

void displayPaymentOptions(bool isOnlineCustomer) {
    cout << "Payment Options:\n";
    if (isOnlineCustomer) {
        cout << "1. Credit Card\n";
    }
    else {
        cout << "1. Credit Card\n";
        cout << "2. Cash\n";
    }
}

PaymentDetails getPaymentDetails(bool isOnlineCustomer, double totalAmount) {
    PaymentDetails payment;
    int choice;

    while (true) {
        displayPaymentOptions(isOnlineCustomer);
        cout << "Select a payment method: ";
        cin >> choice;

        if (isOnlineCustomer && choice != 1) {
            cout << "Invalid choice for online payment. Please select Credit Card.\n";
        }
        else if (!isOnlineCustomer && (choice < 1 || choice > 2)) {
            cout << "Invalid choice. Please choose a valid payment method.\n";
        }
        else {
            break;
        }
    }

    if (choice == 1) {
        payment.method = CREDIT_CARD;
        while (true) {
            cout << "Enter your credit card number (16 digits): ";
            cin >> payment.cardNumber;

            if (validateCreditCard(payment.cardNumber)) {
                break;
            }
            else {
                displayPaymentError("Invalid credit card number. Please try again.");
            }
        }
    }
    else if (choice == 2 && !isOnlineCustomer) {
        payment.method = CASH;
    }

    payment.amount = totalAmount;
    return payment;
}