//THIS PROJECT HELPS UNDERSTAND CLASS , OBJECTS AND ITS MEMBERS IN A BETTER WAY
//A SIMPLE BANK ACCOUNT PROGRAM;
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
# define ll long long
template <typename T>
auto iff(bool condition , T a, T b){
    return condition?a:b;
}//this is a tempelate for basic if and else
unordered_set<ll>usedAccNos;
class Account {
private:
    string name;
    ll acc_no;
    float balance;
    string email;
public:
    Account(string in_name, string in_email,ll in_acc_no, float in_balance) {
        name = in_name;
        acc_no = in_acc_no;
        balance = in_balance;
        email=in_email;
        
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
    //generating random 16 digit account number;
    static ll generateAccNo(){
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<ll>dis(1000000000000000, 9999999999999999);
        long long newNum;
        do{
            newNum=dis(gen);
        }while(usedAccNos.find(newNum)!=usedAccNos.end());
        usedAccNos.insert(newNum);
        return newNum;
    }
    //email validation using regex;
    static bool isValidEmail(const string& email) {
        const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, pattern);
    }
    void Account_info(){
        cout<<" Account Holder: "<<name<<endl;
        cout<<" Account Number: "<<acc_no<<endl;
        cout<<" Balance: "<<balance<<endl;
        cout<<" Email: "<<email<<endl;
    }
    ll getAccountNumber() {
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

                string email;
                while (true){//loop to run till valid email is provided
                    cout<<" Enter your Email Address: ";
                    getline(cin,email);
                    if(Account::isValidEmail(email))break;
                    cout << " Invalid email format! Please try again.\n";
                }
                long long acc_no = Account::generateAccNo();

                cout<<" To open an Account you must have an initial balance of 500 atleast \n Enter your initial balance: ";

                double in_balance;
                cin>>in_balance;
                if (in_balance < 500) {
                    cout << " Insufficient amount to open the account\n";
                } else {
                    accounts.push_back(Account(name, email, acc_no, in_balance));
                    // New formatted message display
                    cout << "|----------------------------------------------|\n";
                    cout << "|      ACCOUNT CREATED SUCCESSFULLY!           |\n";
                    cout << "|                                              |\n";
                    cout << "|   Account Holder: " << left << setw(27) << name << "|\n";
                    cout << "|   Email Address:  " << left << setw(27) << email << "|\n";
                    cout << "|   Account Number: " << left << setw(27) << acc_no << "|\n";
                    cout << "|   Initial Balance: Rs." << left << setw(23) << fixed << setprecision(2) << in_balance << "|\n";
                    cout << "|                                              |\n";
                    cout << "|   * Please remember your Account Number      |\n";
                    cout << "|     to access your account later.            |\n";
                    cout << "|----------------------------------------------|\n";
                }
                break;
            }
                
            case 2:
                {ll account_no;
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
                {ll accNum;
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
                {ll accNum;
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