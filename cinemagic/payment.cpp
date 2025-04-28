#include "payment.h"
#include <iostream>
#include <iomanip>
using namespace std;

bool processPayment(const PaymentDetails& payment) {
    if (payment.method == CREDIT_CARD) {
        cout << "Processing credit card payment...\n";
        cout << "Card Number: " << payment.cardNumber << endl;
    }
    else if (payment.method == CASH) {
        cout << "Processing cash payment...\n";
    }

    cout << "Payment of $" << fixed << setprecision(2) << payment.amount << " successful!\n";
    return true;
}

void displayPaymentOptions(bool isOnlineCustomer) {
    if (isOnlineCustomer) {
        cout << "Payment Options:\n";
        cout << "1. Credit Card\n";
    }
    else {
        cout << "Payment Options:\n";
        cout << "1. Credit Card\n";
        cout << "2. Cash\n";
    }
}

PaymentDetails getPaymentDetails(bool isOnlineCustomer, double totalAmount) {
    PaymentDetails payment;
    int choice;

    displayPaymentOptions(isOnlineCustomer);
    cout << "Select a payment method: ";
    cin >> choice;

    if (isOnlineCustomer && choice != 1) {
        cout << "Invalid choice for online payment. Defaulting to Credit Card.\n";
        choice = 1;
    }

    if (choice == 1) {
        payment.method = CREDIT_CARD;
        cout << "Enter your credit card number: ";
        cin >> payment.cardNumber;
    }
    else if (choice == 2 && !isOnlineCustomer) {
        payment.method = CASH;
    }
    else {
        cout << "Invalid payment method selected. Payment aborted.\n";
        exit(1);
    }

    payment.amount = totalAmount;
    return payment;
}