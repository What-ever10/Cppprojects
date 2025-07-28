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

class Transaction{
private:
    string type;
    double amount;
    string timestamp;
    double newBalance;
public://using the initialiser list for cleaner and more efficient class initialisation
    Transaction(string t, double a, double nb) : 
        type(t), amount(a), newBalance(nb) {
            time_t now = time(0);//get the current system time
            timestamp = ctime(&now);//convert it into readable form
            timestamp.pop_back(); // Remove newline
        }
        //getter functions
        string getType() const { return type; }
        double getAmount() const { return amount; }
        string getTimestamp() const { return timestamp; }
        double getNewBalance() const { return newBalance; }
        //displaying the transaction
        void display() const {
            cout << "│ " << left << setw(12) << type 
                << "│ " << setw(10) << amount 
                << "│ " << setw(25) << timestamp
                << "│ " << setw(10) << newBalance << "│\n";
    }   
};

unordered_set<ll>usedAccNos;

class Account {
protected:
    string name;
    ll acc_no;
    float balance;
    string email;
    vector<Transaction>transactions;
public:
    Account(string in_name, string in_email,ll in_acc_no, float in_balance) {
        name = in_name;
        acc_no = in_acc_no;
        balance = in_balance;
        email=in_email;
        
    }
    virtual ~Account()=default; //virtual destructor for polymorphism

    virtual void applyMonthlyChanges(){}//virtual method to be used in the derived class (polymorphism)

    virtual string getType() const { return "Generic"; }//virtual method to be used in the derived class (polymorphism)

    //depositing money
    void deposit(float amount){
        balance=iff(amount>0,balance+amount,balance);
        if(amount > 0) {
            addTransaction("Deposit", amount);
        }
        string disp = iff(amount > 0, " Rs." + to_string(amount) + " deposited successfully.", string(" Invalid deposit amount!"));
        cout << disp << endl;
    }
    //withdrawing moneys
    virtual void withdraw(float amount){
        int temp=balance;
        balance=iff(amount>0&&amount<=balance,balance-amount,balance);
        string disp=iff(amount>0&&balance!=temp," Rs." + to_string(amount) + " withdrawn successfully.",string(" Invalid withdraw amount or insufficient balance!"));
        if(amount > 0 && amount <= balance) {
            addTransaction("Withdrawal", -amount); // Negative for withdrawals
        }
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
    static bool isValidEmail( string& email) {
        const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, pattern);
    }
    void Account_info(){
        cout<<" Account Holder: "<<name<<endl;
        cout<<" Account Number: "<<acc_no<<endl;
        cout<<" Balance: "<<balance<<endl;
        cout<<" Email: "<<email<<endl;
    }
    // function to store the transaction details
    void addTransaction(string type, double amount) {
        Transaction temp(type,amount,balance);
        transactions.push_back(temp);//could have use the vector.emplace_back() function to construct in place
    }
    ll getAccountNumber() {
        return acc_no;
    }
    //display table for the transaction history
    void showTransactionHistory()  {
        // Header (ASCII version)
        cout << "TRANSACTION HISTORY\n";
        cout << "-----------------------------------------------------------------\n";
        cout << left 
            << setw(12) << "Type" 
            << setw(10) << "Amount" 
            << setw(25) << "Date/Time" 
            << setw(10) << "Balance" << "\n";
        cout << "-----------------------------------------------------------------\n";

        // Data rows (unchanged from original display())
        for(const auto& t : transactions) {
            cout << left 
                << setw(12) << t.getType() 
                << setw(10) << t.getAmount() 
                << setw(25) << t.getTimestamp()
                << setw(10) << t.getNewBalance() << "\n";
        }
        cout << "-----------------------------------------------------------------\n";
    }
};

class SavingsAccount : public Account {
private:
    double interestRate; 
    
public:
    
    SavingsAccount(string name, string email, long long acc_no, float balance, double rate) 
        : Account(name, email, acc_no, balance),
          interestRate(rate) {} 
    
    
    void applyMonthlyChanges() override {
        double interest = balance * interestRate / 12; 
        balance += interest; 
        addTransaction("Interest", interest);
    }
    

    string getType() const override { return "Savings"; }
};

class CheckingAccount : public Account {
private:
    int freeTransactions; 
    const double TRANSACTION_FEE = 10.0; 
    
public:
   
    CheckingAccount(string name, string email, long long acc_no, float balance) 
        : Account(name, email, acc_no, balance), 
          freeTransactions(3) {} 
    
    
    void withdraw(float amount) override {
        Account::withdraw(amount); 
        
       
        if(freeTransactions <= 0) {
            balance -= TRANSACTION_FEE;
            addTransaction("Fee", -TRANSACTION_FEE);
        }
        freeTransactions--;
    }
    

    string getType() const override { return "Checking"; }
};

class BusinessAccount : public Account {
private:
    string companyName; 
    double annualFee;   
    
public:
    
    BusinessAccount(string name, string email, long long acc_no, float balance, double fee) 
        : Account(name, email, acc_no, balance),
          annualFee(fee) {
        companyName = name; 
    }
    
  
    void applyMonthlyChanges() override {
        double monthlyFee = annualFee / 12;
        balance -= monthlyFee;
        addTransaction("Monthly Fee", -monthlyFee);
    }
    
    
    string getType() const override { return "Business"; }
};
int main(){
    vector<Account*>accounts;
    int choice;
    while(true){
        cout << "                        Your very own Bank Management system\n";
        cout << " 1. Create Account\n";
        cout << " 2. Deposit Money\n";
        cout << " 3. Withdraw Money\n";
        cout << " 4. Display Account Details\n";
        cout << " 5. Show Transaction History\n";
        cout << " 6. Exit\n";
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
                    
                    cout << "Select Account Type:\n";
                    cout << "1. Savings\n2. Checking\n3. Business\n";
                    int typeChoice;
                    cin >> typeChoice;

                    
                    Account* newAccount = nullptr;
                    switch(typeChoice) {
                        case 1: 
                            newAccount = new SavingsAccount(name, email, acc_no, in_balance, 0.03);
                            break;
                        case 2:
                            newAccount = new CheckingAccount(name, email, acc_no, in_balance);
                            break;
                        case 3:
                            newAccount = new BusinessAccount(name, email, acc_no, in_balance, 1000);
                            break;
                    }

                    accounts.push_back(newAccount); 
                    
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
                    if(acc->getAccountNumber()==account_no){
                        cout<<" Enter the amount to be deposited:";
                        cin>>amount;
                        acc->deposit(amount);
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
                    if (acc->getAccountNumber() == accNum) {
                        cout << " Enter Withdrawal Amount: ";
                        cin >> amount;
                        acc->withdraw(amount);
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
                    if (acc->getAccountNumber() == accNum) {
                        acc->Account_info();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << " Account not found!\n";
                }
                break;}
            case 5:
                {
                    cout<<"Enter your Account Number";
                    ll acc_no;
                    cin>>acc_no;
                    bool found=false;
                    for(auto & acc:accounts){
                        if(acc->getAccountNumber()==acc_no){
                            acc->showTransactionHistory();
                            found=true;
                            break;
                        }
                    }
                    if(!found)cout<<" Account not found!\n";
                    break;
                }
            case 6:
                cout << " Exiting the system. Thank you!\n";
                break;
            default:
                 cout << " Invalid choice! Please try again.\n";
        }
    }
}