#ifndef RIDER_H
#define RIDER_H

#include "User.h"
#include <vector>
#include <string>

// Rider inherits from User
// Riders book rides and rate drivers
class Rider : public User {
private:
    std::vector<std::string> rideHistory; // stores ride IDs

public:
    Rider() : User() {}

    Rider(std::string id, std::string name, std::string email,
          std::string phone, std::string password)
        : User(id, name, email, phone, password) {}

    std::string getRole() const override {
        return "Rider";
    }

    void addRideToHistory(std::string rideId) {
        rideHistory.push_back(rideId);
    }

    std::vector<std::string> getRideHistory() const {
        return rideHistory;
    }
};

#endif
