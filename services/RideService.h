#ifndef RIDE_SERVICE_H
#define RIDE_SERVICE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include "../models/Ride.h"
#include "../models/Driver.h"
#include "../models/Rider.h"
#include "../enums/Enums.h"
#include "../utils/IdGenerator.h"
#include "../exceptions/CustomException.h"
#include "UserService.h"
#include "FareService.h"
#include "PaymentService.h"

// Core service - manages the entire lifecycle of a ride
class RideService {
private:
    std::unordered_map<std::string, Ride> rides; // rideId -> Ride
    UserService&    userService;
    FareService     fareService;
    PaymentService& paymentService;

public:
    RideService(UserService& us, PaymentService& ps)
        : userService(us), paymentService(ps) {}

    // Rider requests a new ride
    Ride requestRide(std::string riderId, std::string pickupName,
                     std::string dropoffName, double distance,
                     VehicleType vehicleType) {

        // Find an available driver first
        Driver* driver = userService.findAvailableDriver();
        if (driver == nullptr) {
            throw CustomException("No drivers available right now. Please try again later.");
        }

        // Create the ride
        std::string rideId = IdGenerator::generateRideId();
        Location pickup(pickupName);
        Location dropoff(dropoffName);
        Ride ride(rideId, riderId, pickup, dropoff, distance, vehicleType);

        // Calculate and set fare
        double fare = fareService.calculateFare(vehicleType, distance);
        ride.setFare(fare);

        // Assign driver and update statuses
        ride.setDriverId(driver->getUserId());
        ride.setStatus(RideStatus::Requested);
        driver->setStatus(DriverStatus::OnRide);

        // Save ride
        rides[rideId] = ride;

        // Add to rider's history
        userService.getRiderById(riderId).addRideToHistory(rideId);

        std::cout << "\nRide booked! Ride ID: " << rideId << "\n";
        std::cout << "Driver assigned: " << driver->getName() << "\n";
        std::cout << "Estimated Fare : Rs. " << fare << "\n";

        return rides[rideId];
    }

    // Driver accepts the ride
    void acceptRide(std::string rideId, std::string driverId) {
        Ride& ride = getRide(rideId);

        if (ride.getDriverId() != driverId) {
            throw CustomException("This ride is not assigned to you.");
        }

        if (ride.getStatus() != RideStatus::Requested) {
            throw CustomException("Ride cannot be accepted in its current state.");
        }

        ride.setStatus(RideStatus::Accepted);
        std::cout << "Ride accepted! Head to pickup: "
                  << ride.getPickup().getName() << "\n";
    }

    // Driver rejects the ride
    void rejectRide(std::string rideId, std::string driverId) {
        Ride& ride = getRide(rideId);

        if (ride.getDriverId() != driverId) {
            throw CustomException("This ride is not assigned to you.");
        }

        // Free up the driver and cancel the ride
        Driver& driver = userService.getDriverById(driverId);
        driver.setStatus(DriverStatus::Online);
        ride.setStatus(RideStatus::Cancelled);
        std::cout << "Ride rejected.\n";
    }

    // Driver starts the ride
    void startRide(std::string rideId, std::string driverId) {
        Ride& ride = getRide(rideId);

        if (ride.getDriverId() != driverId) {
            throw CustomException("This ride is not assigned to you.");
        }

        if (ride.getStatus() != RideStatus::Accepted) {
            throw CustomException("Ride must be accepted before starting.");
        }

        ride.setStatus(RideStatus::Started);
        std::cout << "Ride started! Heading to: "
                  << ride.getDropoff().getName() << "\n";
    }

    // Driver completes the ride and rider pays
    void completeRide(std::string rideId, std::string driverId, PaymentType paymentType) {
        Ride& ride = getRide(rideId);

        if (ride.getDriverId() != driverId) {
            throw CustomException("This ride is not assigned to you.");
        }

        if (ride.getStatus() != RideStatus::Started) {
            throw CustomException("Ride must be started before completing.");
        }

        // Mark as completed
        ride.setStatus(RideStatus::Completed);

        // Process payment
        paymentService.createPayment(rideId, ride.getFare(), paymentType);
        paymentService.processPayment(rideId);

        // Update driver's earnings and ride history
        Driver& driver = userService.getDriverById(driverId);
        driver.addEarnings(ride.getFare());
        driver.addCompletedRide(rideId);
        driver.setStatus(DriverStatus::Online); // driver is free again

        std::cout << "Ride completed successfully!\n";
        printRideSummary(rideId);
    }

    // Rider cancels a ride (only if not started)
    void cancelRide(std::string rideId, std::string riderId) {
        Ride& ride = getRide(rideId);

        if (ride.getRiderId() != riderId) {
            throw CustomException("This is not your ride.");
        }

        if (ride.getStatus() == RideStatus::Started ||
            ride.getStatus() == RideStatus::Completed) {
            throw CustomException("Cannot cancel a ride that has started or completed.");
        }

        if (ride.getStatus() == RideStatus::Cancelled) {
            throw CustomException("Ride is already cancelled.");
        }

        // Free up the driver if one was assigned
        if (!ride.getDriverId().empty()) {
            Driver& driver = userService.getDriverById(ride.getDriverId());
            driver.setStatus(DriverStatus::Online);
        }

        ride.setStatus(RideStatus::Cancelled);
        std::cout << "Ride cancelled.\n";
    }

    // Print a summary after the ride
    void printRideSummary(std::string rideId) {
        Ride& ride = getRide(rideId);
        Driver& driver = userService.getDriverById(ride.getDriverId());
        Rider& rider   = userService.getRiderById(ride.getRiderId());

        std::cout << "\n========= Ride Summary =========\n";
        std::cout << "Ride ID     : " << ride.getRideId()            << "\n";
        std::cout << "Rider       : " << rider.getName()             << "\n";
        std::cout << "Driver      : " << driver.getName()            << "\n";
        std::cout << "From        : " << ride.getPickup().getName()  << "\n";
        std::cout << "To          : " << ride.getDropoff().getName() << "\n";
        std::cout << "Distance    : " << ride.getDistance() << " km" << "\n";
        std::cout << "Vehicle     : " << ride.getVehicleTypeAsString()<< "\n";
        std::cout << "Fare Paid   : Rs. " << ride.getFare()          << "\n";
        std::cout << "Status      : " << ride.getStatusAsString()    << "\n";
        std::cout << "================================\n";
    }

    // View all rides for a rider
    void viewRideHistory(std::string riderId) {
        Rider& rider = userService.getRiderById(riderId);
        auto history = rider.getRideHistory();

        if (history.empty()) {
            std::cout << "No ride history found.\n";
            return;
        }

        std::cout << "\n--- Your Ride History ---\n";
        for (auto& rideId : history) {
            Ride& ride = rides[rideId];
            std::cout << "Ride ID: " << ride.getRideId()
                      << " | From: " << ride.getPickup().getName()
                      << " -> " << ride.getDropoff().getName()
                      << " | Fare: Rs. " << ride.getFare()
                      << " | Status: " << ride.getStatusAsString() << "\n";
        }
    }

    // Get a ride by ID for driver to view assigned ride
    Ride getRideById(std::string rideId) {
        return getRide(rideId);
    }

    // Get current active ride for a driver
    Ride* getActiveRideForDriver(std::string driverId) {
        for (auto& pair : rides) {
            Ride& ride = pair.second;
            if (ride.getDriverId() == driverId &&
                (ride.getStatus() == RideStatus::Requested ||
                 ride.getStatus() == RideStatus::Accepted ||
                 ride.getStatus() == RideStatus::Started)) {
                return &ride;
            }
        }
        return nullptr;
    }

    // Get current active ride for a rider
    Ride* getActiveRideForRider(std::string riderId) {
        for (auto& pair : rides) {
            Ride& ride = pair.second;
            if (ride.getRiderId() == riderId &&
                (ride.getStatus() == RideStatus::Requested ||
                 ride.getStatus() == RideStatus::Accepted ||
                 ride.getStatus() == RideStatus::Started)) {
                return &ride;
            }
        }
        return nullptr;
    }

    // View completed rides for a driver
    void viewCompletedRidesForDriver(std::string driverId) {
        Driver& driver = userService.getDriverById(driverId);
        auto completedRideIds = driver.getCompletedRides();

        if (completedRideIds.empty()) {
            std::cout << "No completed rides yet.\n";
            return;
        }

        std::cout << "\n--- Your Completed Rides ---\n";
        for (auto& rid : completedRideIds) {
            Ride& ride = rides[rid];
            std::cout << "Ride ID: " << ride.getRideId()
                      << " | From: " << ride.getPickup().getName()
                      << " -> " << ride.getDropoff().getName()
                      << " | Fare: Rs. " << ride.getFare() << "\n";
        }
    }

    FareService& getFareService() { return fareService; }

private:
    // Internal helper to get a ride by ID safely
    Ride& getRide(std::string rideId) {
        if (rides.find(rideId) == rides.end()) {
            throw CustomException("Ride not found: " + rideId);
        }
        return rides[rideId];
    }
};

#endif
