#include <iostream>
#include <string>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT};

using namespace std;

class BankAccount {
private:
    double balance;
    string address, phone, email;
public:
    BankAccount(double initial, string addr, string ph, string mail)
        : balance(initial), address(addr), phone(ph), email(mail) {}

    double getBalance() { return balance; }
    void deposit(double amount) { balance += amount; cout << "Deposit successful. Balance: $" << balance << endl; }
    void withdraw(double amount) { 
        if (amount <= balance) { balance -= amount; cout << "Withdraw successful. Balance: $" << balance << endl; } 
        else cout << "Insufficient balance!\n"; 
    }
    void showInfo() {
        cout << "Address: " << address << ", Phone: " << phone << ", Email: " << email << endl;
        cout << "Balance: $" << balance << endl;
    }
};

class User {
public:
    string name, homeAddr, phone, email;
    bool isSeller;
    string storeName;
    BankAccount* account;
    User(string n="", string addr="", string ph="", string mail="") 
        : name(n), homeAddr(addr), phone(ph), email(mail), isSeller(false), account(nullptr) {}
    void checkStatus() {
        cout << "Name: " << name << endl;
        cout << "Role: " << (isSeller ? "Buyer + Seller" : "Buyer") << endl;
        if (account) account->showInfo(); else cout << "No Bank Account linked.\n";
    }
    void upgradeSeller(string sname) {
        if (!account) { cout << "Need bank account before upgrade!\n"; return; }
        isSeller = true; storeName = sname;
        cout << "Upgraded to Seller with store: " << storeName << endl;
    }
    void createBank(double init, string addr, string ph, string mail) {
        if (account) { cout << "Bank account already exists!\n"; return; }
        account = new BankAccount(init, addr, ph, mail);
        cout << "Bank account created!\n";
    }
};

int main() {
    PrimaryPrompt prompt = LOGIN;
    User* currentUser = nullptr;
    User registered; 

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                if (registered.name == "") { cout << "No user registered yet.\n"; break; }
                {
                    string n; cout << "Enter name: "; cin >> n;
                    if (n != registered.name) { cout << "Login failed.\n"; break; }
                    cout << "Welcome " << n << "!\n";
                    currentUser = &registered;
                    bool stay = true;
                    while (stay) {
                        cout << "\n--- Buyer Menu ---\n";
                        cout << "1. Check Account Status\n";
                        cout << "2. Upgrade to Seller\n";
                        cout << "3. Create/Use Banking Account\n";
                        cout << "4. Logout\n";
                        int sub; cin >> sub;
                        if (sub == 1) currentUser->checkStatus();
                        else if (sub == 2) { string s; cout << "Store name: "; cin >> s; currentUser->upgradeSeller(s); }
                        else if (sub == 3) {
                            if (!currentUser->account) {
                                double d; string a, p, m;
                                cout << "Initial deposit: "; cin >> d;
                                cout << "Address: "; cin >> a;
                                cout << "Phone: "; cin >> p;
                                cout << "Email: "; cin >> m;
                                currentUser->createBank(d,a,p,m);
                            }
                            int b; cout << "1.Deposit 2.Withdraw 3.Check Balance\n"; cin >> b;
                            if (b==1){double amt; cout<<"Amount:";cin>>amt; currentUser->account->deposit(amt);}
                            else if (b==2){double amt; cout<<"Amount:";cin>>amt; currentUser->account->withdraw(amt);}
                            else if (b==3) cout<<"Balance: $"<<currentUser->account->getBalance()<<endl;
                        }
                        else if (sub == 4) { cout<<"Logout.\n"; stay=false; }
                    }
                }
                break;
            case REGISTER:
                cout << "Register selected." << endl;
                {
                    string n,a,p,m; 
                    cout << "Enter name: "; cin>>n;
                    cout << "Enter address: "; cin>>a;
                    cout << "Enter phone: "; cin>>p;
                    cout << "Enter email: "; cin>>m;
                    registered = User(n,a,p,m);
                    cout << "Registration successful.\n";
                }
                break;
            case EXIT:
                cout << "Exiting." << std::endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    return 1;
}
