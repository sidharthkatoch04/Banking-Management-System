int main() {
    loadUsers();
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
    return 0;
}
