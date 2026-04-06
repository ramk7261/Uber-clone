#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "../enums/Enums.h"

class Vehicle {
private:
    std::string vehicleNumber;
    std::string vehicleName;    // e.g. "Honda Activa"
    VehicleType type;

public:
    Vehicle() : vehicleNumber(""), vehicleName(""), type(VehicleType::Car) {}

    Vehicle(std::string number, std::string name, VehicleType vtype) {
        vehicleNumber = number;
        vehicleName   = name;
        type          = vtype;
    }

    std::string getVehicleNumber() const { return vehicleNumber; }
    std::string getVehicleName()   const { return vehicleName; }
    VehicleType getType()          const { return type; }

    void setVehicleNumber(std::string num) { vehicleNumber = num; }
    void setVehicleName(std::string name)  { vehicleName = name; }
    void setType(VehicleType t)            { type = t; }

    // Helper to get vehicle type as string for display
    std::string getTypeAsString() const {
        if (type == VehicleType::Bike) return "Bike";
        if (type == VehicleType::Auto) return "Auto";
        return "Car";
    }
};

#endif
