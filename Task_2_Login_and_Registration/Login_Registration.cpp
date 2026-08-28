#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Simple one-way hash for storing passwords
string hashPassword(const string& password)
{
    const unsigned long long FNV_OFFSET = 14695981039346656037ULL;
    const unsigned long long FNV_PRIME = 1099511628211ULL;

    unsigned long long hash = FNV_OFFSET;

    for (unsigned char c : password)
    {
        hash ^= c;
        hash *= FNV_PRIME;
    }

    stringstream ss;
    ss << hex << hash;

    return ss.str();
}

// Check whether username already exists
bool usernameExists(const string& username)
{
    ifstream file("users.txt");

    string storedUsername;
    string storedPasswordHash;

    while (file >> storedUsername >> storedPasswordHash)
    {
        if (storedUsername == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Registration function
void registerUser()
{
    string username;
    string password;

    cout << "\n====================================\n";
    cout << "          USER REGISTRATION\n";
    cout << "====================================\n";

    cout << "Enter username: ";
    cin >> username;

    // Username validation
    if (username.length() < 3)
    {
        cout << "Error: Username must contain at least 3 characters.\n";
        return;
    }

    // Duplicate username check
    if (usernameExists(username))
    {
        cout << "Error: Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Password validation
    if (password.length() < 6)
    {
        cout << "Error: Password must contain at least 6 characters.\n";
        return;
    }

    // Hash password before storing
    string passwordHash = hashPassword(password);

    // Open file in append mode
    ofstream file("users.txt", ios::app);

    if (!file)
    {
        cout << "Error: Unable to open file.\n";
        return;
    }

    // Store username and hashed password
    file << username << " " << passwordHash << endl;

    file.close();

    cout << "\nRegistration successful!\n";
}

// Login function
void loginUser()
{
    string username;
    string password;

    cout << "\n====================================\n";
    cout << "              USER LOGIN\n";
    cout << "====================================\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Hash entered password for comparison
    string passwordHash = hashPassword(password);

    ifstream file("users.txt");

    if (!file)
    {
        cout << "Error: No registered users found.\n";
        return;
    }

    string storedUsername;
    string storedPasswordHash;

    bool loginSuccessful = false;

    while (file >> storedUsername >> storedPasswordHash)
    {
        if (storedUsername == username &&
            storedPasswordHash == passwordHash)
        {
            loginSuccessful = true;
            break;
        }
    }

    file.close();

    if (loginSuccessful)
    {
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << username << "!\n";
    }
    else
    {
        cout << "\nError: Invalid username or password.\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "     LOGIN & REGISTRATION SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "\nThank you for using the system.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
