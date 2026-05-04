#include "Admin.hpp"
void Admin::adminPanel() {
    string pass;
    cin >> pass;
    if (pass != "admin123") return;
    int choice;
    do {
        cin >> choice;
        int id, index;
        switch (choice) {
        case 1:
            cin >> id;
            index = findUserById(id);
            if (index != -1)
                users[index].frozen = true;
            break;
        case 2:
            cin >> id;
            index = findUserById(id);
            if (index != -1)
                users[index].frozen = false;
            break;
case 3:
cin >> id;
index= findUserById(id);
if(index!=-1){
for(int i = index; i<usercount-1;i++)
    users[i]= users[i+1];
userCount--;
}
break;
        }
    }
        while(choice !=0);
}
