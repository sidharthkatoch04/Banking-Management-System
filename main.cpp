#include "User.hpp"
#include "BankOperations.hpp"
#include "Admin.hpp"
int main() {
    BankOperations bank;
    Admin admin;
    int choice;
    do {
        cin >> choice;
        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2: {
            int index = login();
            if (index != -1) {
                int c;
                do {
                    cin >> c;
                    switch (c) {
                    case 1: bank.deposit(index); break;
                    case 2: bank.withdraw(index); break;
                    case 3: bank.transfer(index); break;
                    case 4: bank.viewTransactions(index); break;
                    }
                } while (c != 0);
            }
            break;
        }
        case 3:
            admin.adminPanel();
            break;
        }
    } while (choice != 0);

    return 0;
}
