#ifndef DRIVER_SERVICE_H
#define DRIVER_SERVICE_H

#include <iostream>
#include <string>
#include "../models/Driver.h"
#include "../models/Vehicle.h"
#include "../enums/Enums.h"
#include "../exceptions/CustomException.h"
#include "UserService.h"

// Handles driver-specific operations
class DriverService {
private:
    UserService& userService; // reference so we can update driver data

public:
    DriverService(UserService& us) : userService(us) {}

    // Driver adds vehicle to their profile
    void addVehicle(std::string driverId, std::string vehicleNumber,
                    std::string vehicleName, VehicleType type) {

        Driver& d = userService.getDriverById(driverId);
        Vehicle v(vehicleNumber, vehicleName, type);
        d.setVehicle(v);
        std::cout << "Vehicle added: " << vehicleName
                  << " (" << vehicleNumber << ")\n";
    }

    // Toggle online/offline
    void setOnlineStatus(std::string driverId, bool goOnline) {
        Driver& d = userService.getDriverById(driverId);

        if (!d.getHasVehicle()) {
            throw CustomException("Please add your vehicle before going online.");
        }

        if (goOnline) {
            d.setStatus(DriverStatus::Online);
            std::cout << "You are now ONLINE. Ready to accept rides.\n";
        } else {
            d.setStatus(DriverStatus::Offline);
            std::cout << "You are now OFFLINE.\n";
        }
    }

    // Show earnings summary
    void showEarnings(std::string driverId) {
        Driver& d = userService.getDriverById(driverId);
        std::cout << "\n--- Earnings Summary ---\n";
        std::cout << "Total Earnings : Rs. " << d.getTotalEarnings() << "\n";
        std::cout << "Rides Completed: " << d.getCompletedRides().size() << "\n";
    }
};

#endif
