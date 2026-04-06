#ifndef FARE_SERVICE_H
#define FARE_SERVICE_H

#include "../enums/Enums.h"
#include "../utils/Constants.h"

// Handles all fare calculation logic
// Keeps pricing logic in one place
class FareService {
public:

    // Calculate fare based on vehicle type and distance
    double calculateFare(VehicleType type, double distanceKm) {
        double baseFare = 0.0;
        double perKm    = 0.0;

        if (type == VehicleType::Bike) {
            baseFare = Constants::BIKE_BASE_FARE;
            perKm    = Constants::BIKE_PER_KM;
        } else if (type == VehicleType::Auto) {
            baseFare = Constants::AUTO_BASE_FARE;
            perKm    = Constants::AUTO_PER_KM;
        } else {
            baseFare = Constants::CAR_BASE_FARE;
            perKm    = Constants::CAR_PER_KM;
        }

        return baseFare + (perKm * distanceKm);
    }

    // Just show the estimate without booking
    void showFareEstimate(double distanceKm) {
        std::cout << "\n--- Fare Estimate for " << distanceKm << " km ---\n";
        std::cout << "Bike : Rs. " << calculateFare(VehicleType::Bike, distanceKm) << "\n";
        std::cout << "Auto : Rs. " << calculateFare(VehicleType::Auto, distanceKm) << "\n";
        std::cout << "Car  : Rs. " << calculateFare(VehicleType::Car,  distanceKm) << "\n";
    }
};

#endif
