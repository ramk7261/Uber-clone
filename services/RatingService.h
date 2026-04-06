#ifndef RATING_SERVICE_H
#define RATING_SERVICE_H

#include <vector>
#include <string>
#include <iostream>
#include "../models/Rating.h"
#include "../utils/Constants.h"
#include "../exceptions/CustomException.h"

// Manages ratings given between riders and drivers
class RatingService {
private:
    std::vector<Rating> ratings;

public:

    // Add a new rating
    void addRating(std::string rideId, std::string givenBy,
                   std::string givenTo, int score, std::string comment) {

        if (score < Constants::MIN_RATING || score > Constants::MAX_RATING) {
            throw CustomException("Rating must be between 1 and 5.");
        }

        Rating r(rideId, givenBy, givenTo, score, comment);
        ratings.push_back(r);
        std::cout << "Rating submitted successfully!\n";
    }

    // Calculate average rating for a user
    double getAverageRating(std::string userId) {
        double total = 0.0;
        int count = 0;

        for (auto& r : ratings) {
            if (r.getGivenTo() == userId) {
                total += r.getScore();
                count++;
            }
        }

        if (count == 0) return 0.0;
        return total / count;
    }

    // Check if a rating already exists for this ride from this user
    bool hasRated(std::string rideId, std::string givenBy) {
        for (auto& r : ratings) {
            if (r.getRideId() == rideId && r.getGivenBy() == givenBy) {
                return true;
            }
        }
        return false;
    }
};

#endif
