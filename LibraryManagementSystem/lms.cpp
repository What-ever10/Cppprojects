//THIS PROJECT HELPS UNDERSTAND CLASS , OBJECTS AND ITS MEMBERS IN A BETTER WAY
//A SIMPLE BANK ACCOUNT PROGRAM;
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
template <typename T>
auto iff(bool condition , T a, T b){
    return condition?a:b;
}//this is a tempelate for basic if and else
class Account {
private:
    string name;
    int acc_no;
    float balance;
public:
    Account(string in_name, int in_acc_no, float in_balance) {
        name = in_name;
        acc_no = in_acc_no;
        balance = in_balance;
    }
    //depositing money
    void deposit(float amount){
        balance=iff(amount>0,balance+amount,balance);
        string disp = iff(amount > 0, " Rs." + to_string(amount) + " deposited successfully.", string(" Invalid deposit amount!"));
        cout << disp << endl;
    }
    //withdrawing moneys
    void withdraw(float amount){
        int temp=balance;
        balance=iff(amount>0&&amount<=balance,balance-amount,balance);
        string disp=iff(amount>0&&balance!=temp," Rs." + to_string(amount) + " withdrawn successfully.",string(" Invalid withdraw amount or insufficient balance!"));
        cout<<disp<<endl;
    }
    void Account_info(){
        cout<<" Account Holder: "<<name<<endl;
        cout<<" Account Number: "<<acc_no<<endl;
        cout<<" Balance: "<<balance<<endl;
    }
    int getAccountNumber() {
        return acc_no;
    }
};

int main(){
    vector<Account>accounts;
    int choice;
    while(true){
        cout << "                        Your very own Bank Management system\n";
        cout << " 1. Create Account\n";
        cout << " 2. Deposit Money\n";
        cout << " 3. Withdraw Money\n";
        cout << " 4. Display Account Details\n";
        cout << " 5. Exit\n";
        cout << " Enter your choice: ";
        cin >> choice;
        switch(choice){//USING SWITCH STATEMENT
            case 1:
                {cout<<" Enter your(AccountHolder's) name: ";
                string name;
                cin.ignore();   // to ignore the newline character left in the input buffer
                getline(cin, name);
                cout<<" Enter your Account Number: ";
                int acc_no;
                cin>>acc_no;
                cout<<" To open an Account you must have an initial balance of 500 atleast \n Enter your initial balance: ";
                double in_balance;
                cin>>in_balance;
                string mssg=iff(in_balance<500," Insufficient amount to open the account","Account successfully created!");
                accounts.push_back(Account(name,acc_no,in_balance));
                cout<<mssg<<endl;
                break;}
            case 2:
                {int account_no;
                double amount;
                cout<<" Enter your Account Number: ";
                cin>>account_no;
                bool found;
                for(auto  &acc:accounts){
                    if(acc.getAccountNumber()==account_no){
                        cout<<" Enter the amount to be deposited:";
                        cin>>amount;
                        acc.deposit(amount);
                        found=true;
                        break;
                    }
                }
                if(!found){
                    cout<<" Account Number is not valid\n";
                }
                break;
            }
            case 3:
                {int accNum;
                double amount;
                cout << " Enter Account Number: ";
                cin >> accNum;
                bool found = false;

                for (auto &acc : accounts) {
                    if (acc.getAccountNumber() == accNum) {
                        cout << " Enter Withdrawal Amount: ";
                        cin >> amount;
                        acc.withdraw(amount);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << " Account not found!\n";
                }
                break;}
            case 4:
                {int accNum;
                cout << " Enter Account Number: ";
                cin >> accNum;
                bool found = false;

                for (auto &acc : accounts) {
                    if (acc.getAccountNumber() == accNum) {
                        acc.Account_info();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << " Account not found!\n";
                }
                break;}
            case 5:
                cout << " Exiting the system. Thank you!\n";
                break;
            default:
                 cout << " Invalid choice! Please try again.\n";
        }
    }
}