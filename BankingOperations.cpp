#include "BankOperations.hpp"
void addTransaction(int index, string type, double amount, int otherId = 0) {
    int t = users[index].transactionCount;
    users[index].transactionType[t] = type;
    users[index].transactionAmount[t] = amount;
    users[index].relatedUserId[t] = otherId;
    users[index].transactionCount++;
}
void BankOperations::deposit(int index) {
    double amount;
    cin >> amount;
    if (amount <= 0) return;
    users[index].balance += amount;
    addTransaction(index, "Deposited", amount);
}
void BankOperations::withdraw(int index) {
    double amount;
    cin >> amount;
    if (amount <= 0 || amount > users[index].balance) return;
    users[index].balance -= amount;
    addTransaction(index, "Withdrawn", amount);
}
void BankOperations::transfer(int index) {
    int id;
    double amount;
    cin >> id;
    int r = findUserById(id);
    if (r == -1) return;
    cin >> amount;
    if (amount <= 0 || amount > users[index].balance) return;
    users[index].balance -= amount;
    users[r].balance += amount;
    addTransaction(index, "Transferred", amount, id);
    addTransaction(r, "Received", amount, users[index].id);
}
void BankOperations::viewTransactions(int index) {
    for (int i = 0; i < users[index].transactionCount, i++) {
        cout << users[index].transactionType[i] << " " << users[index].transactionAmount[i] << endl;
        }
}
