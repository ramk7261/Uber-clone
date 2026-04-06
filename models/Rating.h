#ifndef RATING_H
#define RATING_H

#include <string>

// Stores rating given by one person to another after a ride
class Rating {
private:
    std::string rideId;
    std::string givenBy;     // userId of rater
    std::string givenTo;     // userId of person being rated
    int score;               // 1 to 5
    std::string comment;

public:
    Rating() : rideId(""), givenBy(""), givenTo(""), score(5), comment("") {}

    Rating(std::string rid, std::string from, std::string to, int s, std::string c) {
        rideId  = rid;
        givenBy = from;
        givenTo = to;
        score   = s;
        comment = c;
    }

    std::string getRideId()  const { return rideId; }
    std::string getGivenBy() const { return givenBy; }
    std::string getGivenTo() const { return givenTo; }
    int getScore()           const { return score; }
    std::string getComment() const { return comment; }
};

#endif
