#ifndef ENUMS_H
#define ENUMS_H

// Status of a ride at any point
enum class RideStatus {
    Requested,
    Accepted,
    Started,
    Completed,
    Cancelled
};

// Types of vehicles available
enum class VehicleType {
    Bike,
    Auto,
    Car
};

// Whether the driver is available or not
enum class DriverStatus {
    Online,
    Offline,
    OnRide
};

// How the rider wants to pay
enum class PaymentType {
    Cash,
    Online
};

// Whether payment went through or not
enum class PaymentStatus {
    Pending,
    Success
};

#endif
