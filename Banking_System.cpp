#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ===============================
// Transaction Class
// ===============================
class Transaction
{
private:
    string type;
    double amount;
    string description;

public:
    Transaction(string t, double a, string d)
    {
        type = t;
        amount = a;
        description = d;
    }

    void display() const
    {
        cout << left
             << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << description << endl;
    }
};

// ===============================
// Account Class
// ===============================
class Account
{
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double initialBalance = 0.0)
    {
        accountNumber = accNo;
        balance = initialBalance;

        if (initialBalance > 0)
        {
            transactions.push_back(
                Transaction(
                    "Deposit",
                    initialBalance,
                    "Initial account balance"
                )
            );
        }
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    double getBalance() const
    {
        return balance;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "\nError: Deposit amount must be greater than 0.\n";
            return;
        }

        balance += amount;

        transactions.push_back(
            Transaction(
                "Deposit",
                amount,
                "Cash deposited"
            )
        );

        cout << "\nDeposit successful!\n";
        cout << "New balance: $" << fixed << setprecision(2)
             << balance << endl;
    }

    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "\nError: Withdrawal amount must be greater than 0.\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "\nError: Insufficient balance.\n";
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction(
                "Withdrawal",
                amount,
                "Cash withdrawn"
            )
        );

        cout << "\nWithdrawal successful!\n";
        cout << "New balance: $" << fixed << setprecision(2)
             << balance << endl;

        return true;
    }

    bool transferOut(double amount, int targetAccount)
    {
        if (amount <= 0)
        {
            cout << "\nError: Transfer amount must be greater than 0.\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "\nError: Insufficient balance for transfer.\n";
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction(
                "Transfer Out",
                amount,
                "Transferred to account " +
                    to_string(targetAccount)
            )
        );

        return true;
    }

    void transferIn(double amount, int sourceAccount)
    {
        balance += amount;

        transactions.push_back(
            Transaction(
                "Transfer In",
                amount,
                "Received from account " +
                    to_string(sourceAccount)
            )
        );
    }

    void displayAccountInfo() const
    {
        cout << "\n====================================\n";
        cout << "          ACCOUNT INFORMATION\n";
        cout << "====================================\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Current Balance: $" << fixed
             << setprecision(2) << balance << endl;
        cout << "====================================\n";
    }

    void displayTransactions() const
    {
        cout << "\n==============================================\n";
        cout << "            TRANSACTION HISTORY\n";
        cout << "==============================================\n";

        if (transactions.empty())
        {
            cout << "No transactions found.\n";
        }
        else
        {
            cout << left
                 << setw(15) << "Type"
                 << setw(12) << "Amount"
                 << "Description" << endl;

            cout << "----------------------------------------------\n";

            for (const Transaction &transaction : transactions)
            {
                transaction.display();
            }
        }

        cout << "==============================================\n";
    }
};

// ===============================
// Customer Class
// ===============================
class Customer
{
private:
    int customerId;
    string name;
    string phone;
    vector<Account> accounts;

public:
    Customer(int id, string customerName, string customerPhone)
    {
        customerId = id;
        name = customerName;
        phone = customerPhone;
    }

    int getCustomerId() const
    {
        return customerId;
    }

    string getName() const
    {
        return name;
    }

    bool createAccount(int accountNumber, double initialBalance)
    {
        for (const Account &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                return false;
            }
        }

        accounts.push_back(
            Account(accountNumber, initialBalance)
        );

        return true;
    }

    Account* findAccount(int accountNumber)
    {
        for (Account &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                return &account;
            }
        }

        return nullptr;
    }

    void displayCustomerInfo() const
    {
        cout << "\n====================================\n";
        cout << "          CUSTOMER INFORMATION\n";
        cout << "====================================\n";
        cout << "Customer ID : " << customerId << endl;
        cout << "Name        : " << name << endl;
        cout << "Phone       : " << phone << endl;
        cout << "Accounts    : " << accounts.size() << endl;
        cout << "====================================\n";
    }

    void displayAllAccounts() const
    {
        if (accounts.empty())
        {
            cout << "\nNo accounts found for this customer.\n";
            return;
        }

        cout << "\n====================================\n";
        cout << "             MY ACCOUNTS\n";
        cout << "====================================\n";

        for (const Account &account : accounts)
        {
            cout << "Account: "
                 << account.getAccountNumber()
                 << " | Balance: $"
                 << fixed << setprecision(2)
                 << account.getBalance()
                 << endl;
        }

        cout << "====================================\n";
    }
};

// ===============================
// Banking System
// ===============================
class BankingSystem
{
private:
    vector<Customer> customers;

public:
    void createCustomer()
    {
        int customerId;
        int accountNumber;
        string name;
        string phone;
        double initialBalance;

        cout << "\n====================================\n";
        cout << "            CREATE CUSTOMER\n";
        cout << "====================================\n";

        cout << "Enter customer ID: ";
        cin >> customerId;

        cout << "Enter customer name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

        for (const Customer &customer : customers)
        {
            if (customer.getCustomerId() == customerId)
            {
                cout << "\nError: Customer ID already exists.\n";
                return;
            }
        }

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter initial balance: $";
        cin >> initialBalance;

        if (initialBalance < 0)
        {
            cout << "\nError: Initial balance cannot be negative.\n";
            return;
        }

        Customer newCustomer(
            customerId,
            name,
            phone
        );

        newCustomer.createAccount(
            accountNumber,
            initialBalance
        );

        customers.push_back(newCustomer);

        cout << "\nCustomer and account created successfully!\n";
    }

    Customer* findCustomer(int customerId)
    {
        for (Customer &customer : customers)
        {
            if (customer.getCustomerId() == customerId)
            {
                return &customer;
            }
        }

        return nullptr;
    }

    Account* findAccount(int accountNumber, Customer **owner = nullptr)
    {
        for (Customer &customer : customers)
        {
            Account *account = customer.findAccount(accountNumber);

            if (account != nullptr)
            {
                if (owner != nullptr)
                {
                    *owner = &customer;
                }

                return account;
            }
        }

        return nullptr;
    }

    void depositMoney()
    {
        int accountNumber;
        double amount;

        cout << "\nEnter account number: ";
        cin >> accountNumber;

        Account *account = findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "\nError: Account not found.\n";
            return;
        }

        cout << "Enter deposit amount: $";
        cin >> amount;

        account->deposit(amount);
    }

    void withdrawMoney()
    {
        int accountNumber;
        double amount;

        cout << "\nEnter account number: ";
        cin >> accountNumber;

        Account *account = findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "\nError: Account not found.\n";
            return;
        }

        cout << "Enter withdrawal amount: $";
        cin >> amount;

        account->withdraw(amount);
    }

    void transferFunds()
    {
        int senderAccount;
        int receiverAccount;
        double amount;

        cout << "\nEnter sender account number: ";
        cin >> senderAccount;

        cout << "Enter receiver account number: ";
        cin >> receiverAccount;

        if (senderAccount == receiverAccount)
        {
            cout << "\nError: Sender and receiver cannot be the same.\n";
            return;
        }

        Account *sender = findAccount(senderAccount);
        Account *receiver = findAccount(receiverAccount);

        if (sender == nullptr)
        {
            cout << "\nError: Sender account not found.\n";
            return;
        }

        if (receiver == nullptr)
        {
            cout << "\nError: Receiver account not found.\n";
            return;
        }

        cout << "Enter transfer amount: $";
        cin >> amount;

        if (sender->transferOut(amount, receiverAccount))
        {
            receiver->transferIn(amount, senderAccount);

            cout << "\nFund transfer successful!\n";
            cout << "Transferred $" << fixed
                 << setprecision(2) << amount
                 << " from account "
                 << senderAccount
                 << " to account "
                 << receiverAccount
                 << ".\n";
        }
    }

    void showAccount()
    {
        int accountNumber;

        cout << "\nEnter account number: ";
        cin >> accountNumber;

        Customer *owner = nullptr;
        Account *account = findAccount(
            accountNumber,
            &owner
        );

        if (account == nullptr)
        {
            cout << "\nError: Account not found.\n";
            return;
        }

        owner->displayCustomerInfo();
        account->displayAccountInfo();
    }

    void showTransactions()
    {
        int accountNumber;

        cout << "\nEnter account number: ";
        cin >> accountNumber;

        Account *account = findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "\nError: Account not found.\n";
            return;
        }

        account->displayTransactions();
    }

    void run()
    {
        int choice;

        do
        {
            cout << "\n========================================\n";
            cout << "          CODEALPHA BANKING SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Create Customer & Account\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Transfer Funds\n";
            cout << "5. View Account Information\n";
            cout << "6. View Transaction History\n";
            cout << "7. Exit\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    createCustomer();
                    break;

                case 2:
                    depositMoney();
                    break;

                case 3:
                    withdrawMoney();
                    break;

                case 4:
                    transferFunds();
                    break;

                case 5:
                    showAccount();
                    break;

                case 6:
                    showTransactions();
                    break;

                case 7:
                    cout << "\nThank you for using CodeAlpha Banking System.\n";
                    break;

                default:
                    cout << "\nError: Invalid choice.\n";
            }

        } while (choice != 7);
    }
};

int main()
{
    BankingSystem system;
    system.run();

    return 0;
}