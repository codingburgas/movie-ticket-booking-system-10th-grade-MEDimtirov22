#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

enum PaymentMethod {
    CREDIT_CARD,
    CASH
};

struct PaymentDetails {
    PaymentMethod method;
    std::string cardNumber;
    double amount;
};

bool processPayment(const PaymentDetails& payment);
void displayPaymentOptions(bool isOnlineCustomer);
PaymentDetails getPaymentDetails(bool isOnlineCustomer, double totalAmount);

#endif