#ifndef ADMIN_HPP
#define ADMIN_HPP
#include "User.hpp"
class Admin {
private:
    const string ADMIN_PASSWORD = "admin123";
public:
    void adminPanel();
    void viewAllUsers();
};
#endif
