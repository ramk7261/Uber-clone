#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <exception>
#include <string>

// Simple custom exception class for our app
class CustomException : public std::exception {
private:
    std::string message;

public:
    CustomException(std::string msg) {
        message = msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif
