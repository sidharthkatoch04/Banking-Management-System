#include "BankingOperations.hpp"
#include <iostream>
using namespace std;

bool ok(int i){ 
    if(i<0||i>=userCount){cout<<"Invalid user\n";return false;} 
    if(users[i].frozen){cout<<"Account frozen\n";return false;} 
    return true; 
}

void record(int i,string t,double a,int other=0){
    addTransaction(i,t,a,other);
}

void checkBalance(int i){
    if(!ok(i)) return;
    cout<<"Balance: "<<users[i].balance<<endl;
}

void deposit(int i){
    if(!ok(i)) return;
    double a; cout<<"Deposit amount: "; cin>>a;
    if(a<=0){cout<<"Invalid amount\n";return;}
    users[i].balance+=a; record(i,"Deposit",a);
    cout<<"Deposit successful\n";
}

void withdraw(int i){
    if(!ok(i)) return;
    double a; cout<<"Withdraw amount: "; cin>>a;
    if(a<=0||a>users[i].balance){cout<<"Invalid amount\n";return;}
    users[i].balance-=a; record(i,"Withdraw",a);
    cout<<"Withdrawal successful\n";
}

void transferMoney(int s){
    if(!ok(s)) return;
    int id; double a;
    cout<<"Receiver ID: "; cin>>id;
    int r=findUserById(id);
    if(r==-1){cout<<"User not found\n";return;}
    cout<<"Amount: "; cin>>a;
    if(a<=0||a>users[s].balance){cout<<"Invalid amount\n";return;}
    users[s].balance-=a; users[r].balance+=a;
    record(s,"Transfer Sent",a,id);
    record(r,"Transfer Received",a,users[s].id);
    cout<<"Transfer successful\n";
}

void viewTransactions(int i){
    if(!ok(i)) return;
    if(users[i].transactionCount==0){cout<<"No transactions\n";return;}
    cout<<"\nTransaction History:\n";
    for(int k=0;k<users[i].transactionCount;k++){
        cout<<k+1<<". "<<users[i].transactionType[k]
            <<" | "<<users[i].transactionAmount[k];
        if(users[i].relatedUserId[k]!=0)
            cout<<" | ID "<<users[i].relatedUserId[k];
        cout<<endl;
    }
}