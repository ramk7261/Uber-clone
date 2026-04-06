#ifndef LOCATION_H
#define LOCATION_H

#include <string>

// Simple location with just a name (no real GPS in this project)
class Location {
private:
    std::string name;

public:
    Location() : name("") {}

    Location(std::string n) {
        name = n;
    }

    std::string getName() const {
        return name;
    }

    void setName(std::string n) {
        name = n;
    }
};

#endif
