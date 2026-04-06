#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include "Vehicle.h"
#include "../enums/Enums.h"
#include <vector>
#include <string>

// Driver inherits from User
// Drivers accept rides, complete them, and earn money
class Driver : public User {
private:
    Vehicle vehicle;
    DriverStatus status;
    double totalEarnings;
    std::vector<std::string> completedRides; // ride IDs
    bool hasVehicle; // flag to check if vehicle has been added

public:
    Driver() : User(), status(DriverStatus::Offline),
               totalEarnings(0.0), hasVehicle(false) {}

    Driver(std::string id, std::string name, std::string email,
           std::string phone, std::string password)
        : User(id, name, email, phone, password),
          status(DriverStatus::Offline),
          totalEarnings(0.0),
          hasVehicle(false) {}

    std::string getRole() const override {
        return "Driver";
    }

    // Vehicle management
    void setVehicle(Vehicle v) {
        vehicle = v;
        hasVehicle = true;
    }

    Vehicle getVehicle() const { return vehicle; }
    bool getHasVehicle()  const { return hasVehicle; }

    // Status management
    DriverStatus getStatus() const { return status; }
    void setStatus(DriverStatus s) { status = s; }

    std::string getStatusAsString() const {
        if (status == DriverStatus::Online)  return "Online";
        if (status == DriverStatus::Offline) return "Offline";
        return "On Ride";
    }

    // Earnings
    double getTotalEarnings() const { return totalEarnings; }
    void addEarnings(double amount) { totalEarnings += amount; }

    // Ride history
    void addCompletedRide(std::string rideId) {
        completedRides.push_back(rideId);
    }

    std::vector<std::string> getCompletedRides() const {
        return completedRides;
    }
};

#endif
