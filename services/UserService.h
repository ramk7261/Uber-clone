#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "../models/Rider.h"
#include "../models/Driver.h"
#include "../utils/IdGenerator.h"
#include "../exceptions/CustomException.h"

// Handles registration and login for both Riders and Drivers
class UserService {
private:
    // email -> Rider
    std::unordered_map<std::string, Rider> riders;

    // email -> Driver
    std::unordered_map<std::string, Driver> drivers;

    // userId -> email (for quick lookup by ID)
    std::unordered_map<std::string, std::string> riderIdToEmail;
    std::unordered_map<std::string, std::string> driverIdToEmail;

public:

    // Register a new rider
    Rider registerRider(std::string name, std::string email,
                        std::string phone, std::string password) {

        if (riders.find(email) != riders.end()) {
            throw CustomException("A rider with this email already exists.");
        }

        std::string id = IdGenerator::generateUserId();
        Rider r(id, name, email, phone, password);
        riders[email] = r;
        riderIdToEmail[id] = email;
        std::cout << "Rider registered successfully! Your ID: " << id << "\n";
        return r;
    }

    // Register a new driver
    Driver registerDriver(std::string name, std::string email,
                          std::string phone, std::string password) {

        if (drivers.find(email) != drivers.end()) {
            throw CustomException("A driver with this email already exists.");
        }

        std::string id = IdGenerator::generateUserId();
        Driver d(id, name, email, phone, password);
        drivers[email] = d;
        driverIdToEmail[id] = email;
        std::cout << "Driver registered successfully! Your ID: " << id << "\n";
        return d;
    }

    // Login a rider - returns the Rider object if credentials match
    Rider loginRider(std::string email, std::string password) {
        if (riders.find(email) == riders.end()) {
            throw CustomException("Rider not found with this email.");
        }

        Rider& r = riders[email];
        if (r.getPassword() != password) {
            throw CustomException("Incorrect password.");
        }

        std::cout << "Welcome back, " << r.getName() << "!\n";
        return r;
    }

    // Login a driver
    Driver loginDriver(std::string email, std::string password) {
        if (drivers.find(email) == drivers.end()) {
            throw CustomException("Driver not found with this email.");
        }

        Driver& d = drivers[email];
        if (d.getPassword() != password) {
            throw CustomException("Incorrect password.");
        }

        std::cout << "Welcome back, " << d.getName() << "!\n";
        return d;
    }

    // Get a rider by ID (we need this to update ride history etc.)
    Rider& getRiderById(std::string riderId) {
        if (riderIdToEmail.find(riderId) == riderIdToEmail.end()) {
            throw CustomException("Rider not found.");
        }
        return riders[riderIdToEmail[riderId]];
    }

    // Get a driver by ID
    Driver& getDriverById(std::string driverId) {
        if (driverIdToEmail.find(driverId) == driverIdToEmail.end()) {
            throw CustomException("Driver not found.");
        }
        return drivers[driverIdToEmail[driverId]];
    }

    // Find the first available online driver who has a vehicle
    // Simple logic - just pick the first online driver we find
    Driver* findAvailableDriver() {
        for (auto& pair : drivers) {
            Driver& d = pair.second;
            if (d.getStatus() == DriverStatus::Online && d.getHasVehicle()) {
                return &d;
            }
        }
        return nullptr; // no driver available
    }
};

#endif
