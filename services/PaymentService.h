#ifndef PAYMENT_SERVICE_H
#define PAYMENT_SERVICE_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "../models/Payment.h"
#include "../utils/IdGenerator.h"
#include "../exceptions/CustomException.h"

// Handles creating and processing payments
class PaymentService {
private:
    // paymentId -> Payment object
    std::unordered_map<std::string, Payment> payments;

    // rideId -> paymentId (to find payment for a ride quickly)
    std::unordered_map<std::string, std::string> rideToPayment;

public:

    // Create a payment record for a ride
    Payment createPayment(std::string rideId, double amount, PaymentType type) {
        std::string pid = IdGenerator::generatePaymentId();
        Payment p(pid, rideId, amount, type, PaymentStatus::Pending);
        payments[pid] = p;
        rideToPayment[rideId] = pid;
        return p;
    }

    // Process the payment (simulated - always succeeds)
    void processPayment(std::string rideId) {
        if (rideToPayment.find(rideId) == rideToPayment.end()) {
            throw CustomException("No payment found for this ride.");
        }

        std::string pid = rideToPayment[rideId];
        payments[pid].setStatus(PaymentStatus::Success);
        std::cout << "Payment of Rs. " << payments[pid].getAmount()
                  << " via " << payments[pid].getTypeAsString()
                  << " was successful!\n";
    }

    // Get payment details for a ride
    Payment getPaymentByRideId(std::string rideId) {
        if (rideToPayment.find(rideId) == rideToPayment.end()) {
            throw CustomException("Payment not found.");
        }
        return payments[rideToPayment[rideId]];
    }
};

#endif
