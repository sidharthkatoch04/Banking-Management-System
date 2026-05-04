#include "User.hpp"

User users[MAX_USERS];
int userCount = 0;

User::User() {
    balance = 0;
    frozen = false;
    transactionCount = 0;
}

int findUserByUsername(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username)
            return i;
    }
    return -1;
}

int findUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id)
            return i;
    }
    return -1;
}

void registerUser() {
    try {
        string username, password;

        cout << "Enter username: ";
        cin >> username;

        if (findUserByUsername(username) != -1)
            throw "Username already exists!";

        cout << "Enter password: ";
        cin >> password;

        users[userCount].id = userCount + 1;
        users[userCount].username = username;
        users[userCount].password = password;

        userCount++;

        cout << "Registration successful!\n";
    }
    catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }
}
int login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    int index = findUserByUsername(username);
    if (index == -1) return -1;
    if (users[index].password != password) return -1;
    if (users[index].frozen) return -1;
    return index;
}
void User::showMenu(int index) {
    cout << "User Menu";
}
