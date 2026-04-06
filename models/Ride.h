#ifndef RIDE_H
#define RIDE_H

#include <string>
#include "Location.h"
#include "../enums/Enums.h"

// Ride holds all the info about a single trip
class Ride {
private:
    std::string rideId;
    std::string riderId;
    std::string driverId;    // empty until a driver accepts
    Location    pickup;
    Location    dropoff;
    double      distance;    // in km
    double      fare;
    RideStatus  status;
    VehicleType vehicleType; // what type the rider requested

public:
    Ride() : rideId(""), riderId(""), driverId(""),
             distance(0.0), fare(0.0),
             status(RideStatus::Requested),
             vehicleType(VehicleType::Car) {}

    Ride(std::string rid, std::string riderid, Location pick,
         Location drop, double dist, VehicleType vtype) {
        rideId      = rid;
        riderId     = riderid;
        driverId    = "";
        pickup      = pick;
        dropoff     = drop;
        distance    = dist;
        fare        = 0.0;
        status      = RideStatus::Requested;
        vehicleType = vtype;
    }

    // Getters
    std::string getRideId()     const { return rideId; }
    std::string getRiderId()    const { return riderId; }
    std::string getDriverId()   const { return driverId; }
    Location    getPickup()     const { return pickup; }
    Location    getDropoff()    const { return dropoff; }
    double      getDistance()   const { return distance; }
    double      getFare()       const { return fare; }
    RideStatus  getStatus()     const { return status; }
    VehicleType getVehicleType() const { return vehicleType; }

    // Setters
    void setDriverId(std::string id)  { driverId = id; }
    void setFare(double f)            { fare = f; }
    void setStatus(RideStatus s)      { status = s; }

    // Helper to print status nicely
    std::string getStatusAsString() const {
        switch (status) {
            case RideStatus::Requested:  return "Requested";
            case RideStatus::Accepted:   return "Accepted";
            case RideStatus::Started:    return "Started";
            case RideStatus::Completed:  return "Completed";
            case RideStatus::Cancelled:  return "Cancelled";
        }
        return "Unknown";
    }

    std::string getVehicleTypeAsString() const {
        if (vehicleType == VehicleType::Bike) return "Bike";
        if (vehicleType == VehicleType::Auto) return "Auto";
        return "Car";
    }
};

#endif
