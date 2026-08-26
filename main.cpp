#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// BANK ACCOUNT CLASS
// ============================================================

class BankAccount
{
private:
    int accountNumber;
    string accountHolder;
    string phoneNumber;
    string accountType;
    double balance;

public:
    // Default constructor
    BankAccount()
    {
        accountNumber = 0;
        balance = 0.0;
    }

    // Parameterized constructor
    BankAccount(int accNo, string name, string phone,
                string type, double bal)
    {
        accountNumber = accNo;
        accountHolder = name;
        phoneNumber = phone;
        accountType = type;
        balance = bal;
    }

    // Getters
    int getAccountNumber() const
    {
        return accountNumber;
    }

    string getAccountHolder() const
    {
        return accountHolder;
    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }

    string getAccountType() const
    {
        return accountType;
    }

    double getBalance() const
    {
        return balance;
    }

    // Deposit money
    void deposit(double amount)
    {
        balance += amount;
    }

    // Withdraw money
    bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance)
        {
            return false;
        }

        balance -= amount;
        return true;
    }

    // Display account information
    void displayAccount() const
    {
        cout << "\n---------------------------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Phone Number   : " << phoneNumber << endl;
        cout << "Account Type   : " << accountType << endl;
        cout << "Balance        : Rs. "
             << fixed << setprecision(2) << balance << endl;
        cout << "---------------------------------------------\n";
    }

    // Save account in file (pipe-separated format)
    void saveToFile(ofstream &file) const
    {
        file << accountNumber << "|"
             << accountHolder << "|"
             << phoneNumber << "|"
             << accountType << "|"
             << balance << endl;
    }
};


// ============================================================
// BANK MANAGEMENT SYSTEM CLASS
// ============================================================

class BankSystem
{
private:
    vector<BankAccount> accounts;

    const string accountFile = "accounts.txt";
    const string transactionFile = "transactions.txt";

    // Find account by account number
    BankAccount* findAccount(int accountNumber)
    {
        for (auto &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                return &account;
            }
        }

        return nullptr;
    }

    // Generate next unique account number starting from 1001
    int generateAccountNumber()
    {
        int maxNumber = 1000;

        for (const auto &account : accounts)
        {
            if (account.getAccountNumber() > maxNumber)
            {
                maxNumber = account.getAccountNumber();
            }
        }

        return maxNumber + 1;
    }

    // Get current date and time as a formatted string
    string getDateTime()
    {
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);

        char buffer[80];

        strftime(
            buffer,
            sizeof(buffer),
            "%Y-%m-%d %H:%M:%S",
            localTime
        );

        return string(buffer);
    }

    // Save transaction record to transactions.txt
    void saveTransaction(
        int accountNumber,
        string type,
        double amount,
        double balance
    )
    {
        ofstream file(transactionFile, ios::app);

        if (!file)
        {
            cout << "Error: Unable to save transaction.\n";
            return;
        }

        file << getDateTime() << "|"
             << accountNumber << "|"
             << type << "|"
             << fixed << setprecision(2)
             << amount << "|"
             << balance << endl;

        file.close();
    }

    // Save all accounts to accounts.txt
    void saveAccounts()
    {
        ofstream file(accountFile);

        if (!file)
        {
            cout << "Error: Unable to save account data.\n";
            return;
        }

        for (const auto &account : accounts)
        {
            account.saveToFile(file);
        }

        file.close();
    }

public:
    // ========================================================
    // LOAD ACCOUNTS FROM FILE
    // ========================================================

    void loadAccounts()
    {
        ifstream file(accountFile);

        if (!file)
        {
            return;
        }

        accounts.clear();

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            size_t pos4 = line.find('|', pos3 + 1);

            if (
                pos1 == string::npos ||
                pos2 == string::npos ||
                pos3 == string::npos ||
                pos4 == string::npos
            )
            {
                continue;
            }

            try
            {
                int accountNumber =
                    stoi(line.substr(0, pos1));

                string name =
                    line.substr(
                        pos1 + 1,
                        pos2 - pos1 - 1
                    );

                string phone =
                    line.substr(
                        pos2 + 1,
                        pos3 - pos2 - 1
                    );

                string type =
                    line.substr(
                        pos3 + 1,
                        pos4 - pos3 - 1
                    );

                double balance =
                    stod(line.substr(pos4 + 1));

                accounts.emplace_back(
                    accountNumber,
                    name,
                    phone,
                    type,
                    balance
                );
            }
            catch (...)
            {
                continue;
            }
        }

        file.close();
    }


    // ========================================================
    // CREATE ACCOUNT
    // ========================================================

    void createAccount()
    {
        string name;
        string phone;
        string type;
        double initialDeposit;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n========== CREATE NEW ACCOUNT ==========\n";

        cout << "Enter account holder name: ";
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
            return;
        }

        cout << "Enter phone number: ";
        getline(cin, phone);

        if (phone.empty())
        {
            cout << "Phone number cannot be empty.\n";
            return;
        }

        cout << "Enter account type (Savings/Current): ";
        getline(cin, type);

        if (type.empty())
        {
            cout << "Account type cannot be empty.\n";
            return;
        }

        cout << "Enter initial deposit: Rs. ";
        cin >> initialDeposit;

        if (cin.fail() || initialDeposit < 0)
        {
            cout << "Invalid deposit amount.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        int accountNumber = generateAccountNumber();

        BankAccount newAccount(
            accountNumber,
            name,
            phone,
            type,
            initialDeposit
        );

        accounts.push_back(newAccount);

        saveAccounts();

        if (initialDeposit > 0)
        {
            saveTransaction(
                accountNumber,
                "Initial Deposit",
                initialDeposit,
                initialDeposit
            );
        }

        cout << "\nAccount created successfully!\n";
        cout << "Your Account Number is: "
             << accountNumber << endl;
    }


    // ========================================================
    // DISPLAY ALL ACCOUNTS
    // ========================================================

    void displayAllAccounts()
    {
        cout << "\n========== ALL ACCOUNTS ==========\n";

        if (accounts.empty())
        {
            cout << "No accounts found.\n";
            return;
        }

        for (const auto &account : accounts)
        {
            account.displayAccount();
        }
    }


    // ========================================================
    // SEARCH ACCOUNT
    // ========================================================

    void searchAccount()
    {
        int accountNumber;

        cout << "\n========== SEARCH ACCOUNT ==========\n";

        cout << "Enter account number: ";
        cin >> accountNumber;

        if (cin.fail())
        {
            cout << "Invalid account number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        BankAccount *account =
            findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        account->displayAccount();
    }


    // ========================================================
    // DEPOSIT MONEY
    // ========================================================

    void depositMoney()
    {
        int accountNumber;
        double amount;

        cout << "\n========== DEPOSIT MONEY ==========\n";

        cout << "Enter account number: ";
        cin >> accountNumber;

        if (cin.fail())
        {
            cout << "Invalid account number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        BankAccount *account =
            findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter amount to deposit: Rs. ";
        cin >> amount;

        if (cin.fail() || amount <= 0)
        {
            cout << "Invalid amount.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        account->deposit(amount);

        saveAccounts();

        saveTransaction(
            accountNumber,
            "Deposit",
            amount,
            account->getBalance()
        );

        cout << "\nDeposit successful.\n";
        cout << "New Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance() << endl;
    }


    // ========================================================
    // WITHDRAW MONEY
    // ========================================================

    void withdrawMoney()
    {
        int accountNumber;
        double amount;

        cout << "\n========== WITHDRAW MONEY ==========\n";

        cout << "Enter account number: ";
        cin >> accountNumber;

        if (cin.fail())
        {
            cout << "Invalid account number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        BankAccount *account =
            findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Current Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << endl;

        cout << "Enter amount to withdraw: Rs. ";
        cin >> amount;

        if (cin.fail() || amount <= 0)
        {
            cout << "Invalid amount.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        if (!account->withdraw(amount))
        {
            cout << "Transaction failed.\n";
            cout << "Insufficient balance or invalid amount.\n";
            return;
        }

        saveAccounts();

        saveTransaction(
            accountNumber,
            "Withdrawal",
            amount,
            account->getBalance()
        );

        cout << "\nWithdrawal successful.\n";
        cout << "Remaining Balance: Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << endl;
    }


    // ========================================================
    // DELETE ACCOUNT
    // ========================================================

    void deleteAccount()
    {
        int accountNumber;

        cout << "\n========== DELETE ACCOUNT ==========\n";

        cout << "Enter account number: ";
        cin >> accountNumber;

        if (cin.fail())
        {
            cout << "Invalid account number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        for (auto it = accounts.begin();
             it != accounts.end();
             ++it)
        {
            if (it->getAccountNumber() == accountNumber)
            {
                cout << "\nAccount Found:\n";

                it->displayAccount();

                char confirmation;

                cout << "Are you sure you want to delete "
                        "this account? (Y/N): ";

                cin >> confirmation;

                // Clear any trailing characters in the buffer
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                if (
                    confirmation == 'Y' ||
                    confirmation == 'y'
                )
                {
                    accounts.erase(it);

                    saveAccounts();

                    cout << "Account deleted successfully.\n";
                }
                else
                {
                    cout << "Deletion cancelled.\n";
                }

                return;
            }
        }

        cout << "Account not found.\n";
    }


    // ========================================================
    // TRANSACTION HISTORY
    // ========================================================

    void transactionHistory()
    {
        int accountNumber;

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        cout << "Enter account number: ";
        cin >> accountNumber;

        if (cin.fail())
        {
            cout << "Invalid account number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return;
        }

        BankAccount *account =
            findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        ifstream file(transactionFile);

        if (!file)
        {
            cout << "No transaction history found.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\n";
        cout << left
             << setw(20) << "Date & Time"
             << setw(18) << "Type"
             << setw(15) << "Amount"
             << setw(15) << "Balance"
             << endl;

        cout << string(68, '-') << endl;

        while (getline(file, line))
        {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            size_t pos4 = line.find('|', pos3 + 1);

            if (
                pos1 == string::npos ||
                pos2 == string::npos ||
                pos3 == string::npos ||
                pos4 == string::npos
            )
            {
                continue;
            }

            string date =
                line.substr(0, pos1);

            string accNo =
                line.substr(
                    pos1 + 1,
                    pos2 - pos1 - 1
                );

            string type =
                line.substr(
                    pos2 + 1,
                    pos3 - pos2 - 1
                );

            string amount =
                line.substr(
                    pos3 + 1,
                    pos4 - pos3 - 1
                );

            string balance =
                line.substr(pos4 + 1);

            try
            {
                if (stoi(accNo) == accountNumber)
                {
                    found = true;

                    cout << left
                         << setw(20) << date
                         << setw(18) << type
                         << setw(15) << ("Rs. " + amount)
                         << setw(15) << ("Rs. " + balance)
                         << endl;
                }
            }
            catch (...)
            {
                continue;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No transactions found for this account.\n";
        }
    }


    // ========================================================
    // MAIN MENU
    // ========================================================

    void menu()
    {
        int choice;

        do
        {
            cout << "\n";
            cout << "=============================================\n";
            cout << "          BANK MANAGEMENT SYSTEM\n";
            cout << "=============================================\n";

            cout << "1. Create New Account\n";
            cout << "2. Display All Accounts\n";
            cout << "3. Search Account\n";
            cout << "4. Deposit Money\n";
            cout << "5. Withdraw Money\n";
            cout << "6. Transaction History\n";
            cout << "7. Delete Account\n";
            cout << "8. Exit\n";

            cout << "=============================================\n";

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number.\n";

                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                continue;
            }

            switch (choice)
            {
                case 1:
                    createAccount();
                    break;

                case 2:
                    displayAllAccounts();
                    break;

                case 3:
                    searchAccount();
                    break;

                case 4:
                    depositMoney();
                    break;

                case 5:
                    withdrawMoney();
                    break;

                case 6:
                    transactionHistory();
                    break;

                case 7:
                    deleteAccount();
                    break;

                case 8:
                    cout << "\nThank you for using Bank Management System.\n";
                    break;

                default:
                    cout << "Invalid choice. Please select 1-8.\n";
            }

        } while (choice != 8);
    }
};


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    BankSystem bank;

    // Load previously saved accounts
    bank.loadAccounts();

    // Start application
    bank.menu();

    return 0;
}
