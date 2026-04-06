#ifndef CONSTANTS_H
#define CONSTANTS_H

// All fare-related constants in one place
// Makes it easy to update prices later
namespace Constants {

    // Base fare per vehicle type
    const double BIKE_BASE_FARE   = 30.0;
    const double AUTO_BASE_FARE   = 40.0;
    const double CAR_BASE_FARE    = 60.0;

    // Per km rate
    const double BIKE_PER_KM      = 8.0;
    const double AUTO_PER_KM      = 10.0;
    const double CAR_PER_KM       = 15.0;

    // Rating bounds
    const int MIN_RATING = 1;
    const int MAX_RATING = 5;
}

#endif
