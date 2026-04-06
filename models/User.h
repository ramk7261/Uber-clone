#ifndef USER_H
#define USER_H

#include <string>

// Base class for both Rider and Driver
// Contains common fields every user has
class User {
protected:
    std::string userId;
    std::string name;
    std::string email;
    std::string phone;
    std::string password;

public:
    User() : userId(""), name(""), email(""), phone(""), password("") {}

    User(std::string id, std::string n, std::string e,
         std::string ph, std::string pass) {
        userId   = id;
        name     = n;
        email    = e;
        phone    = ph;
        password = pass;
    }

    virtual ~User() {}

    // Getters
    std::string getUserId()  const { return userId; }
    std::string getName()    const { return name; }
    std::string getEmail()   const { return email; }
    std::string getPhone()   const { return phone; }
    std::string getPassword() const { return password; }

    // Setters
    void setUserId(std::string id)   { userId = id; }
    void setName(std::string n)      { name = n; }
    void setEmail(std::string e)     { email = e; }
    void setPhone(std::string ph)    { phone = ph; }
    void setPassword(std::string p)  { password = p; }

    // Just a marker so subclasses can identify themselves
    virtual std::string getRole() const = 0;
};

#endif
