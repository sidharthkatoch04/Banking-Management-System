#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 100;
const int MAX_TRANSACTIONS = 200;

class User {
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
};

User users[MAX_USERS];
int userCount = 0;

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

void addTransaction(int index, string type, double amount, int otherId = 0) {

    int t = users[index].transactionCount;
    if (t >= MAX_TRANSACTIONS) {
        cout << "Transaction limit reached.\n";
        return;
    }

    users[index].transactionType[t] = type;
    users[index].transactionAmount[t] = amount;
    users[index].relatedUserId[t] = otherId;
    users[index].transactionCount++;
}

void registerUser() {

    if (userCount >= MAX_USERS) {
        cout << "User limit reached.\n";
        return;
    }

    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (findUserByUsername(username) != -1) {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    users[userCount].id = userCount + 1;
    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].balance = 0;
    users[userCount].frozen = false;
    users[userCount].transactionCount = 0;

    userCount++;

    cout << "Registration successful!\n";
}

int login() {

    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    int index = findUserByUsername(username);

    if (index == -1) {
        cout << "User not found.\n";
        return -1;
    }

    if (users[index].password != password) {
        cout << "Wrong password.\n";
        return -1;
    }

    if (users[index].frozen) {
        cout << "Account is frozen.\n";
        return -1;
    }

    cout << "Login successful!\n";
    return index;
}

void viewProfile(int index) {

    cout << "\n--- USER PROFILE ---\n";
    cout << "User ID: " << users[index].id << endl;
    cout << "Username: " << users[index].username << endl;
    cout << "Balance: " << users[index].balance << endl;
    cout << "Account Status: "
         << (users[index].frozen ? "Frozen" : "Active")
         << endl;
}

void changePassword(int index) {

    string oldPass, newPass;
    cout << "Enter current password: ";
    cin >> oldPass;

    if (oldPass != users[index].password) {
        cout << "Incorrect password.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPass;
    users[index].password = newPass;

    cout << "Password changed successfully.\n";
}

void checkBalance(int index) {
    cout << "Current Balance: " << users[index].balance << endl;
}

void deposit(int index) {

    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    users[index].balance += amount;
    addTransaction(index, "Deposited", amount);

    cout << "Deposit successful.\n";
}

void withdraw(int index) {

    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0 || amount > users[index].balance) {
        cout << "Invalid amount.\n";
        return;
    }

    users[index].balance -= amount;
    addTransaction(index, "Withdrawn", amount);

    cout << "Withdrawal successful.\n";
}

void transferMoney(int index) {

    int receiverId;
    double amount;

    cout << "Enter receiver ID: ";
    cin >> receiverId;

    int receiverIndex = findUserById(receiverId);

    if (receiverIndex == -1) {
        cout << "User not found.\n";
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (amount <= 0 || amount > users[index].balance) {
        cout << "Invalid amount.\n";
        return;
    }

    users[index].balance -= amount;
    users[receiverIndex].balance += amount;

    addTransaction(index, "Transferred", amount, receiverId);
    addTransaction(receiverIndex, "Received", amount, users[index].id);

    cout << "Transfer successful.\n";
}

void viewTransactions(int index) {

    cout << "\n--- Transaction History ---\n";

    if (users[index].transactionCount == 0) {
        cout << "No transactions yet.\n";
        return;
    }

    for (int i = 0; i < users[index].transactionCount; i++) {

        string type = users[index].transactionType[i];
        double amount = users[index].transactionAmount[i];
        int otherId = users[index].relatedUserId[i];

        if (type == "Deposited")
            cout << "Deposited: " << amount << endl;
        else if (type == "Withdrawn")
            cout << "Withdrawn: " << amount << endl;
        else if (type == "Transferred")
            cout << "Transferred: " << amount << " to ID " << otherId << endl;
        else if (type == "Received")
            cout << "Received: " << amount << " from ID " << otherId << endl;
    }
}

bool closeAccount(int index) {

    char confirm;
    cout << "Are you sure you want to close your account? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < userCount - 1; i++) {
            users[i] = users[i + 1];
        }
        userCount--;
        cout << "Account closed successfully.\n";
        return true;
    } else {
        cout << "Account not closed.\n";
        return false;
    }
}

void adminPanel() {

    string password;
    cout << "Enter admin password: ";
    cin >> password;

    if (password != "admin123") {
        cout << "Wrong password.\n";
        return;
    }

    int choice;

    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. View Users\n";
        cout << "2. Freeze Account\n";
        cout << "3. Unfreeze Account\n";
        cout << "4. Delete User\n";
        cout << "0. Exit\n";
        cin >> choice;

        int id, index;

        switch (choice) {

        case 1:
            for (int i = 0; i < userCount; i++) {
                cout << "ID: " << users[i].id
                     << " | Username: " << users[i].username
                     << " | Balance: " << users[i].balance
                     << " | Status: "
                     << (users[i].frozen ? "Frozen" : "Active")
                     << endl;
            }
            break;

        case 2:
            cout << "Enter user ID: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                users[index].frozen = true;
                cout << "Account frozen.\n";
            }
            break;

        case 3:
            cout << "Enter user ID: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                users[index].frozen = false;
                cout << "Account unfrozen.\n";
            }
            break;

        case 4:
            cout << "Enter user ID: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                for (int i = index; i < userCount - 1; i++) {
                    users[i] = users[i + 1];
                }
                userCount--;
                cout << "User deleted.\n";
            }
            break;
        }

    } while (choice != 0);
}

void userMenu(int index) {

    int choice;
    bool logout = false;

    do {
        cout << "\n--- USER MENU ---\n";
        cout << "1. View Profile\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Transaction History\n";
        cout << "7. Change Password\n";
        cout << "8. Close Account\n";
        cout << "0. Logout\n";
        cin >> choice;

        switch (choice) {
        case 1: viewProfile(index); break;
        case 2: checkBalance(index); break;
        case 3: deposit(index); break;
        case 4: withdraw(index); break;
        case 5: transferMoney(index); break;
        case 6: viewTransactions(index); break;
        case 7: changePassword(index); break;
        case 8:
            if (closeAccount(index))
                logout = true;
            break;
        }

    } while (choice != 0 && !logout);
}

int main() {

    int choice;

    do {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Admin Panel\n";
        cout << "0. Exit\n";
        cin >> choice;

        switch (choice) {

        case 1:
            registerUser();
            break;

        case 2: {
            int index = login();
            if (index != -1) {
                userMenu(index);
            }
            break;
        }

        case 3:
            adminPanel();
            break;
        }

    } while (choice != 0);

    cout << "Thank you for using our bank system!\n";
    return 0;
}