#ifndef BANKOPERATIONS_HPP
#define BANKOPERATIONS_HPP

#include "User.hpp"

class BankOperations {
public:
    void deposit (int index);
    void withdraw (int index);
    void transfer (int index);
    void viewTransactions (int index);
};

#endif
