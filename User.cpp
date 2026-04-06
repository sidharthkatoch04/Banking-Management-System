#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 100;
const int MAX_TRANSACTIONS = 200;

//ABSTRACT BASE CLASS:-
class Account {
public:
    virtual void showMenu(int index) = 0;
};

//USER CLASS:-
class User : public Account {
public:
    int id;
    string username;
    string password;
    double balance;
    bool frozen;

    string transactionType[MAX_TRANSACTIONS];
    double transactionAmount[MAX_TRANSACTIONS];
    int relatedUserId[MAX_TRANSACTIONS];
    int transactionCount;

    User();
    void showMenu(int index);
};

//FUNCTIONS:-
int findUserByUsername(string username);
int findUserById(int id);
void registerUser();
int login();

extern User users[MAX_USERS];
extern int userCount;

#endif
