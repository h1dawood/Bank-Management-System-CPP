#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For currency formatting
#include <fstream> // For File I/O

using namespace std;

// --- 1. DATA STRUCTURE ---
struct Account {
    int id;
    string name;
    string phone;
    string password;
    double balance;
    vector<string> logs; 
};

// Global Vector to act as our Database
vector<Account> accounts;
const string FILENAME = "bank_data.txt";

// --- FUNCTION PROTOTYPES ---
void loadData();
void saveData();
void createAccount();
void displayAllAccounts(); // Admin feature
int findAccountIndex(int id); // Helper function
void userMenu(int index); // The menu after login
void deposit(int index);
void withdraw(int index);
void transfer(int index);
void showLogs(int index);
void searchAccount();

// --- MAIN FUNCTION ---
int main() {
    loadData(); // Load data from text file at startup

    int choice;
    while (true) {
        system("cls");
        cout << "===================================\n";
        cout << "===================================\n";
        cout << "    BANK MANAGEMENT SYSTEM (ECU)   \n";
        cout << "===================================\n";
        cout << "1. Admin: Create New Account\n";
        cout << "2. Admin: Display All Customers\n";
        cout << "3. Admin: Search Account by ID\n";
        cout << "4. User: Login to Account\n";
        cout << "5. Exit & Save\n";
        cout << "===================================\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            displayAllAccounts();
            break;
        case 3:
            searchAccount(); 
            break;
        case 4: {
            int id;
            string pass;
            cout << "\n--- LOGIN ---\n";
            cout << "Enter Account ID: ";
            cin >> id;

            int index = findAccountIndex(id);
            if (index != -1) {
                cout << "Enter Password: ";
                cin >> pass;
                if (accounts[index].password == pass) {
                    cout << "Login Successful! Welcome " << accounts[index].name << ".\n";
                    system("pause");
                    userMenu(index);
                }
                else {
                    cout << "Error: Incorrect Password.\n";
                    system("pause");
                }
            }
            else {
                cout << "Error: Account ID not found.\n";
                system("pause");
            }
            break;
        }
        case 5:
            saveData();
            cout << "Data Saved. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid Option.\n";
            system("pause");
        }

    }

// --- CORE FUNCTIONS ---

// 1. Create Account
void createAccount() {
    Account newAcc;

    // Auto-generate ID (Start at 1000 if empty, else last ID + 1)
    if (accounts.empty()) newAcc.id = 1001;
    else newAcc.id = accounts.back().id + 1;

    cout << "\n--- CREATE NEW ACCOUNT ---\n";
    cin.ignore(); // Clear buffer
    cout << "Enter Full Name: ";
    getline(cin, newAcc.name);     cout << "Enter Phone Number: ";
    cin >> newAcc.phone;
    cout << "Set Password: ";
    cin >> newAcc.password;

    newAcc.balance = 0.0; // Initial balance
    newAcc.logs.push_back("Account Created.");

    accounts.push_back(newAcc); // Add to memory
    saveData(); // Save to file immediately

    cout << "Account Created Successfully! Your Account ID is: " << newAcc.id << "\n";
    system("pause");
}

// 2. Display All (Admin)
void displayAllAccounts() {
    cout << "\n--- ALL CUSTOMER ACCOUNTS ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Phone" << setw(10) << "Balance" << endl;
    cout << "---------------------------------------------------------\n";

    for (const auto& acc : accounts) {
        cout << left << setw(10) << acc.id
            << setw(20) << acc.name
            << setw(15) << acc.phone
            << "$" << fixed << setprecision(2) << acc.balance << endl;
    }
    cout << "\n";
    system("pause");
}

// 3. User Menu (After Login)
void userMenu(int index) {
    int choice;
    while (true) {
        system("cls");
        cout << "===================================\n";
        cout << "    WELCOME " << accounts[index].name << "\n";
        cout << "    Balance: $" << fixed << setprecision(2) << accounts[index].balance << "\n";
        cout << "===================================\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Transfer Money\n";
        cout << "4. View Transaction Logs\n";
        cout << "5. Logout\n";
        cout << "===================================\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: deposit(index); break;
        case 2: withdraw(index); break;
        case 3: transfer(index); break;
        case 4: showLogs(index); break;
        case 5: return;
        default: cout << "Invalid choice.\n";
        }
    }
}
// 4. Search Account by ID 
void searchAccount() {
    int id;
    cout << "\n--- SEARCH ACCOUNT ---\n";
    cout << "Enter Account ID to find: ";
    cin >> id;

    int index = findAccountIndex(id); 

    if (index != -1) {
        cout << "\nAccount Found!\n";
        cout << "----------------------------\n";
        cout << "ID      : " << accounts[index].id << endl;
        cout << "Name    : " << accounts[index].name << endl;
        cout << "Phone   : " << accounts[index].phone << endl;
        cout << "Balance : $" << fixed << setprecision(2) << accounts[index].balance << endl;
        cout << "----------------------------\n";
    }
    else {
        cout << "\nError: Account ID " << id << " does not exist.\n";
    }
    system("pause");
}

// --- TRANSACTION FUNCTIONS ---

void deposit(int index) {
    double amount;
    cout << "\nEnter amount to deposit: $";
    cin >> amount;

    if (amount > 0) {
        accounts[index].balance += amount;
        accounts[index].logs.push_back("Deposited: $" + to_string(amount));
        saveData();
        cout << "Deposit Successful! New Balance: $" << accounts[index].balance << "\n";
    }
    else {
        cout << "Invalid amount.\n";
    }
    system("pause");
}

void withdraw(int index) {
    double amount;
    string passCheck;

    cout << "\nEnter amount to withdraw: $";
    cin >> amount;

    // Security Check
    cout << "Verify Password: ";
    cin >> passCheck;

    if (passCheck == accounts[index].password) {
        if (amount > 0 && amount <= accounts[index].balance) {
            accounts[index].balance -= amount;
            accounts[index].logs.push_back("Withdrawn: $" + to_string(amount));
            saveData();
            cout << "Withdrawal Successful! New Balance: $" << accounts[index].balance << "\n";
        }
        else {
            cout << "Insufficient funds or invalid amount.\n";
        }
    }
    else {
        cout << "Incorrect Password. Transaction Cancelled.\n";
    }
    system("pause");
}

// The "Transfer" logic from your whiteboard
void transfer(int index) {
    int receiverID;
    double amount;

    cout << "\n--- TRANSFER MONEY ---\n";
    cout << "Enter Receiver Account ID: ";
    cin >> receiverID;

    int rIndex = findAccountIndex(receiverID);

    if (rIndex == -1) {
        cout << "Receiver ID not found.\n";
        system("pause");
        return;
    }

    if (accounts[index].id == receiverID) {
        cout << "You cannot transfer money to yourself.\n";
        system("pause");
        return;
    }

    cout << "Enter Amount to Transfer: $";
    cin >> amount;

    if (amount > accounts[index].balance) {
        cout << "Insufficient Balance.\n";
        system("pause");
        return;
    }


    char confirm;
    cout << "Transfer $" << amount << " to " << accounts[rIndex].name << "? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        // Execute Transfer
        accounts[index].balance -= amount;
        accounts[rIndex].balance += amount;

        // Logs
        accounts[index].logs.push_back("Transferred $" + to_string(amount) + " to " + accounts[rIndex].name);
        accounts[rIndex].logs.push_back("Received $" + to_string(amount) + " from " + accounts[index].name);

        saveData();
        cout << "Transfer Successful!\n";
    }
    else {
        cout << "Transfer Cancelled.\n";
    }
    system("pause");
}

void showLogs(int index) {
    cout << "\n--- TRANSACTION HISTORY ---\n";
    if (accounts[index].logs.empty()) {
        cout << "No transactions yet.\n";
    }
    else {
        for (string log : accounts[index].logs) {
            cout << "- " << log << endl;
        }
    }
    cout << "\n";
    system("pause");
}

// --- HELPER & FILE FUNCTIONS ---

int findAccountIndex(int id) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].id == id) {
            return i;
        }
    }
    return -1; // Not found
}

// Save Data to Text File
void saveData() {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (const auto& acc : accounts) {
            // Format: ID Name Phone Password Balance
            file << acc.id << " " << acc.name << " " << acc.phone << " "
                << acc.password << " " << acc.balance << endl;
        }
        file.close();
    }
}

// Load Data from Text File
void loadData() {
    ifstream file(FILENAME);
    if (file.is_open()) {
        Account temp;
        // While reading: ID Name Phone Password Balance
        while (file >> temp.id) {
            file.ignore(); // skip space
            file >> temp.name >> temp.phone >> temp.password >> temp.balance;
            temp.logs.push_back("Data Loaded from file.");
            accounts.push_back(temp);
        }
        file.close();
    }
}
