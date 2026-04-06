#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include "../enums/Enums.h"

class Payment {
private:
    std::string paymentId;
    std::string rideId;
    double amount;
    PaymentType  type;
    PaymentStatus status;

public:
    Payment() : paymentId(""), rideId(""), amount(0.0),
                type(PaymentType::Cash), status(PaymentStatus::Pending) {}

    Payment(std::string pid, std::string rid, double amt,
            PaymentType ptype, PaymentStatus pstatus) {
        paymentId = pid;
        rideId    = rid;
        amount    = amt;
        type      = ptype;
        status    = pstatus;
    }

    std::string getPaymentId()  const { return paymentId; }
    std::string getRideId()     const { return rideId; }
    double getAmount()          const { return amount; }
    PaymentType getType()       const { return type; }
    PaymentStatus getStatus()   const { return status; }

    void setStatus(PaymentStatus s) { status = s; }

    std::string getTypeAsString() const {
        return (type == PaymentType::Cash) ? "Cash" : "Online";
    }

    std::string getStatusAsString() const {
        return (status == PaymentStatus::Success) ? "Success" : "Pending";
    }
};

#endif
