#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <string>

// Simple utility to generate unique IDs for users, rides, payments
class IdGenerator {
private:
    static int userCount;
    static int rideCount;
    static int paymentCount;

public:
    static std::string generateUserId() {
        userCount++;
        return "USR" + std::to_string(userCount);
    }

    static std::string generateRideId() {
        rideCount++;
        return "RIDE" + std::to_string(rideCount);
    }

    static std::string generatePaymentId() {
        paymentCount++;
        return "PAY" + std::to_string(paymentCount);
    }
};

#endif
