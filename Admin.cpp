#include "Admin.hpp"
void Admin::viewAllUsers() {
    cout << "\n--- All Users ---\n";
    for (int i = 0; i < userCount; i++) {
        cout << "ID: " << users[i].id
             << " | Name: " << users[i].username
             << " | Balance: " << users[i].balance
             << " | Status: " << (users[i].frozen ? "Frozen" : "Active")
             << endl;
    }
}
void Admin::adminPanel() {
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;
    if (pass != ADMIN_PASSWORD) {
        cout << "Wrong password!\n";
        return;
    }
    int choice;
    do {
        cout << "\n1. Freeze Account\n2. Unfreeze Account\n3. Delete User\n4. View All Users\n0. Exit\n";
        cin >> choice;
        int id, index;
        switch (choice) {
        case 1:
            cout << "Enter user ID to freeze: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                users[index].frozen = true;
                cout << "Account frozen.\n";
            } else cout << "User not found.\n";
            break;
        case 2:
            cout << "Enter user ID to unfreeze: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                users[index].frozen = false;
                cout << "Account unfrozen.\n";
            } else cout << "User not found.\n";
            break;
        case 3:
            cout << "Enter user ID to delete: ";
            cin >> id;
            index = findUserById(id);
            if (index != -1) {
                for (int i = index; i < userCount - 1; i++)
                    users[i] = users[i + 1];
                userCount--;
                cout << "User deleted.\n";
            } else cout << "User not found.\n";
            break;
        case 4:
            viewAllUsers();
            break;
        case 0:
            cout << "Exiting admin panel.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
