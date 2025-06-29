#pragma once

#include <string>

enum class PaymentMethod {
    CREDIT_CARD,
    CASH
};

inline std::string paymentMethodToString(PaymentMethod method) {
    switch (method) {
    case PaymentMethod::CREDIT_CARD: return "CREDIT_CARD";
    case PaymentMethod::CASH: return "CASH";
    default: return "UNKNOWN";
    }
}

struct PaymentDetails {
    PaymentMethod method;
    std::string cardNumber;
    double amount;
};

bool processPayment(const PaymentDetails& payment);
void displayPaymentOptions(bool isOnlineCustomer);
PaymentDetails getPaymentDetails(bool isOnlineCustomer, double totalAmount);
bool validateCreditCard(const std::string& cardNumber);
