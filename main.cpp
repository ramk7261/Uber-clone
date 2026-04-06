#include <iostream>
#include <string>
#include <limits>

#include "models/User.h"
#include "models/Rider.h"
#include "models/Driver.h"
#include "models/Vehicle.h"
#include "models/Ride.h"
#include "models/Payment.h"
#include "enums/Enums.h"
#include "utils/IdGenerator.h"
#include "utils/Constants.h"
#include "services/UserService.h"
#include "services/RideService.h"
#include "services/DriverService.h"
#include "services/FareService.h"
#include "services/PaymentService.h"
#include "services/RatingService.h"
#include "exceptions/CustomException.h"

using namespace std;

// ─── Forward declarations ────────────────────────────────────────────────────
void showMainMenu();
void showRiderMenu(Rider& rider, RideService& rideService,
                   RatingService& ratingService, FareService& fareService);
void showDriverMenu(Driver& driver, RideService& rideService,
                    DriverService& driverService, RatingService& ratingService,
                    UserService& userService);

// ─── Small helpers ───────────────────────────────────────────────────────────

// Clear the input buffer after a bad read
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Read a full line safely
string readLine(const string& prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

// Read a double safely
double readDouble(const string& prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        clearInput();
        cout << "Invalid input. Try again: ";
    }
    clearInput();
    return val;
}

// Read an int safely
int readInt(const string& prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        clearInput();
        cout << "Invalid input. Try again: ";
    }
    clearInput();
    return val;
}

// ─── Vehicle type picker ─────────────────────────────────────────────────────
VehicleType pickVehicleType() {
    cout << "Vehicle type:\n";
    cout << "  1. Bike\n  2. Auto\n  3. Car\n";
    int ch = readInt("Choice: ");
    if (ch == 1) return VehicleType::Bike;
    if (ch == 2) return VehicleType::Auto;
    return VehicleType::Car;
}

// ─── RIDER MENU ──────────────────────────────────────────────────────────────
void showRiderMenu(Rider& rider, RideService& rideService,
                   RatingService& ratingService, FareService& fareService) {

    bool loggedIn = true;

    while (loggedIn) {
        cout << "\n======== Rider Menu (" << rider.getName() << ") ========\n";
        cout << "1. Book a Ride\n";
        cout << "2. View Fare Estimate\n";
        cout << "3. View Ride History\n";
        cout << "4. Cancel Ride\n";
        cout << "5. Rate Driver\n";
        cout << "6. Logout\n";
        cout << "=========================================\n";

        int choice = readInt("Enter choice: ");

        if (choice == 1) {
            // ── Book a Ride ──────────────────────────────────────────────
            cout << "\n--- Book a Ride ---\n";
            string pickup  = readLine("Pickup location : ");
            string dropoff = readLine("Dropoff location: ");
            double dist    = readDouble("Distance (km)   : ");

            // Show fare estimate before booking
            fareService.showFareEstimate(dist);

            VehicleType vtype = pickVehicleType();

            try {
                Ride ride = rideService.requestRide(
                    rider.getUserId(), pickup, dropoff, dist, vtype);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            // ── Fare Estimate ────────────────────────────────────────────
            double dist = readDouble("Enter distance (km): ");
            fareService.showFareEstimate(dist);

        } else if (choice == 3) {
            // ── Ride History ─────────────────────────────────────────────
            try {
                rideService.viewRideHistory(rider.getUserId());
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 4) {
            // ── Cancel Ride ──────────────────────────────────────────────
            // Find active ride for this rider
            Ride* active = rideService.getActiveRideForRider(rider.getUserId());
            if (active == nullptr) {
                cout << "You have no active ride to cancel.\n";
            } else {
                cout << "Your active Ride ID: " << active->getRideId() << "\n";
                try {
                    rideService.cancelRide(active->getRideId(), rider.getUserId());
                } catch (CustomException& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }

        } else if (choice == 5) {
            // ── Rate Driver ──────────────────────────────────────────────
            string rideId = readLine("Enter Ride ID to rate: ");
            try {
                Ride ride = rideService.getRideById(rideId);

                if (ride.getRiderId() != rider.getUserId()) {
                    cout << "This is not your ride.\n";
                } else if (ride.getStatus() != RideStatus::Completed) {
                    cout << "You can only rate after the ride is completed.\n";
                } else if (ratingService.hasRated(rideId, rider.getUserId())) {
                    cout << "You have already rated this ride.\n";
                } else {
                    int score     = readInt("Rating (1-5): ");
                    string comment = readLine("Comment       : ");
                    ratingService.addRating(rideId, rider.getUserId(),
                                            ride.getDriverId(), score, comment);
                }
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 6) {
            // ── Logout ───────────────────────────────────────────────────
            cout << "Logged out. Goodbye, " << rider.getName() << "!\n";
            loggedIn = false;

        } else {
            cout << "Invalid option. Try again.\n";
        }
    }
}

// ─── DRIVER MENU ─────────────────────────────────────────────────────────────
void showDriverMenu(Driver& driver, RideService& rideService,
                    DriverService& driverService, RatingService& ratingService,
                    UserService& userService) {

    bool loggedIn = true;

    while (loggedIn) {
        // Refresh driver status from service (since UserService stores real state)
        Driver& liveDriver = userService.getDriverById(driver.getUserId());

        cout << "\n======== Driver Menu (" << liveDriver.getName() << ") ========\n";
        cout << "Status: " << liveDriver.getStatusAsString() << "\n";
        cout << "-----------------------------------------\n";
        cout << "1. Add / Update Vehicle\n";
        cout << "2. Go Online\n";
        cout << "3. Go Offline\n";
        cout << "4. View Assigned Ride\n";
        cout << "5. Accept Ride\n";
        cout << "6. Reject Ride\n";
        cout << "7. Start Ride\n";
        cout << "8. Complete Ride\n";
        cout << "9. View Earnings\n";
        cout << "10. View Completed Rides\n";
        cout << "11. Rate Rider\n";
        cout << "12. Logout\n";
        cout << "=========================================\n";

        int choice = readInt("Enter choice: ");

        if (choice == 1) {
            // ── Add Vehicle ──────────────────────────────────────────────
            cout << "\n--- Add Vehicle ---\n";
            string vehicleNum  = readLine("Vehicle number (e.g. MH12AB1234): ");
            string vehicleName = readLine("Vehicle name   (e.g. Honda City) : ");
            VehicleType vtype  = pickVehicleType();
            try {
                driverService.addVehicle(liveDriver.getUserId(),
                                         vehicleNum, vehicleName, vtype);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            // ── Go Online ────────────────────────────────────────────────
            try {
                driverService.setOnlineStatus(liveDriver.getUserId(), true);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 3) {
            // ── Go Offline ───────────────────────────────────────────────
            try {
                driverService.setOnlineStatus(liveDriver.getUserId(), false);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 4) {
            // ── View Assigned Ride ───────────────────────────────────────
            Ride* active = rideService.getActiveRideForDriver(liveDriver.getUserId());
            if (active == nullptr) {
                cout << "No ride assigned to you right now.\n";
            } else {
                cout << "\n--- Your Current Ride ---\n";
                cout << "Ride ID  : " << active->getRideId()            << "\n";
                cout << "Pickup   : " << active->getPickup().getName()  << "\n";
                cout << "Dropoff  : " << active->getDropoff().getName() << "\n";
                cout << "Distance : " << active->getDistance() << " km" << "\n";
                cout << "Fare     : Rs. " << active->getFare()          << "\n";
                cout << "Status   : " << active->getStatusAsString()    << "\n";
            }

        } else if (choice == 5) {
            // ── Accept Ride ──────────────────────────────────────────────
            Ride* active = rideService.getActiveRideForDriver(liveDriver.getUserId());
            if (active == nullptr) {
                cout << "No ride to accept.\n";
            } else {
                try {
                    rideService.acceptRide(active->getRideId(), liveDriver.getUserId());
                } catch (CustomException& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }

        } else if (choice == 6) {
            // ── Reject Ride ──────────────────────────────────────────────
            Ride* active = rideService.getActiveRideForDriver(liveDriver.getUserId());
            if (active == nullptr) {
                cout << "No ride to reject.\n";
            } else {
                try {
                    rideService.rejectRide(active->getRideId(), liveDriver.getUserId());
                } catch (CustomException& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }

        } else if (choice == 7) {
            // ── Start Ride ───────────────────────────────────────────────
            Ride* active = rideService.getActiveRideForDriver(liveDriver.getUserId());
            if (active == nullptr) {
                cout << "No ride to start.\n";
            } else {
                try {
                    rideService.startRide(active->getRideId(), liveDriver.getUserId());
                } catch (CustomException& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }

        } else if (choice == 8) {
            // ── Complete Ride ────────────────────────────────────────────
            Ride* active = rideService.getActiveRideForDriver(liveDriver.getUserId());
            if (active == nullptr) {
                cout << "No ride in progress.\n";
            } else {
                cout << "Payment method:\n  1. Cash\n  2. Online\n";
                int pChoice = readInt("Choice: ");
                PaymentType ptype = (pChoice == 1) ? PaymentType::Cash
                                                    : PaymentType::Online;
                try {
                    rideService.completeRide(active->getRideId(),
                                             liveDriver.getUserId(), ptype);
                } catch (CustomException& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }

        } else if (choice == 9) {
            // ── View Earnings ────────────────────────────────────────────
            try {
                driverService.showEarnings(liveDriver.getUserId());
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 10) {
            // ── View Completed Rides ─────────────────────────────────────
            try {
                rideService.viewCompletedRidesForDriver(liveDriver.getUserId());
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 11) {
            // ── Rate Rider ───────────────────────────────────────────────
            string rideId = readLine("Enter Ride ID to rate: ");
            try {
                Ride ride = rideService.getRideById(rideId);

                if (ride.getDriverId() != liveDriver.getUserId()) {
                    cout << "This is not your ride.\n";
                } else if (ride.getStatus() != RideStatus::Completed) {
                    cout << "Ride must be completed before rating.\n";
                } else if (ratingService.hasRated(rideId, liveDriver.getUserId())) {
                    cout << "You have already rated this ride.\n";
                } else {
                    int score      = readInt("Rating (1-5): ");
                    string comment = readLine("Comment      : ");
                    ratingService.addRating(rideId, liveDriver.getUserId(),
                                            ride.getRiderId(), score, comment);
                }
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 12) {
            // ── Logout ───────────────────────────────────────────────────
            cout << "Logged out. Goodbye, " << liveDriver.getName() << "!\n";
            loggedIn = false;

        } else {
            cout << "Invalid option. Try again.\n";
        }
    }
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    // All services created once and passed around by reference
    UserService    userService;
    PaymentService paymentService;
    RideService    rideService(userService, paymentService);
    DriverService  driverService(userService);
    RatingService  ratingService;
    FareService    fareService;

    cout << "=========================================\n";
    cout << "     Welcome to UberClone (C++ LLD)      \n";
    cout << "=========================================\n";

    bool running = true;

    while (running) {
        cout << "\n============= Main Menu =============\n";
        cout << "1. Register as Rider\n";
        cout << "2. Register as Driver\n";
        cout << "3. Login as Rider\n";
        cout << "4. Login as Driver\n";
        cout << "5. Exit\n";
        cout << "=====================================\n";

        int choice = readInt("Enter choice: ");

        if (choice == 1) {
            // ── Register Rider ───────────────────────────────────────────
            cout << "\n--- Rider Registration ---\n";
            string name  = readLine("Name    : ");
            string email = readLine("Email   : ");
            string phone = readLine("Phone   : ");
            string pass  = readLine("Password: ");
            try {
                userService.registerRider(name, email, phone, pass);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            // ── Register Driver ──────────────────────────────────────────
            cout << "\n--- Driver Registration ---\n";
            string name  = readLine("Name    : ");
            string email = readLine("Email   : ");
            string phone = readLine("Phone   : ");
            string pass  = readLine("Password: ");
            try {
                userService.registerDriver(name, email, phone, pass);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 3) {
            // ── Login Rider ──────────────────────────────────────────────
            cout << "\n--- Rider Login ---\n";
            string email = readLine("Email   : ");
            string pass  = readLine("Password: ");
            try {
                Rider rider = userService.loginRider(email, pass);
                showRiderMenu(rider, rideService, ratingService, fareService);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 4) {
            // ── Login Driver ─────────────────────────────────────────────
            cout << "\n--- Driver Login ---\n";
            string email = readLine("Email   : ");
            string pass  = readLine("Password: ");
            try {
                Driver driver = userService.loginDriver(email, pass);
                showDriverMenu(driver, rideService, driverService,
                               ratingService, userService);
            } catch (CustomException& e) {
                cout << "Error: " << e.what() << "\n";
            }

        } else if (choice == 5) {
            cout << "Goodbye! Thanks for using UberClone.\n";
            running = false;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
