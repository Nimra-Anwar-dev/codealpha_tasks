# 🔐 CodeAlpha Login and Registration System

A C++ **Login and Registration System** developed as part of the **CodeAlpha C++ Programming Internship**.

## 📌 Project Overview

This project implements a basic user authentication system using C++. It allows users to register an account with a username and password and later log in using their registered credentials.

The system includes:

* User registration
* Input validation
* Duplicate username checking
* Password hashing before file storage
* Login credential verification
* File-based credential storage
* Success and error messages
* Menu-driven console interface

## 🎯 Requirements Implemented

The project implements the required Login and Registration functionality described by CodeAlpha:

* A registration function that accepts username and password
* Input validation and duplicate username checking
* User credentials stored in a file
* A login function that reads stored credentials and verifies user identity
* Appropriate success and error messages for registration and login

## ✨ Features

### 👤 User Registration

The registration process allows a user to create an account by entering a username and password.

The system:

1. Accepts the username.
2. Validates the username.
3. Checks whether the username already exists.
4. Accepts the password.
5. Validates the password.
6. Hashes the password before storing it.
7. Saves the username and hashed password to `users.txt`.
8. Displays the registration result.

### ✅ Username Validation

The program checks the username before registration.

A username must contain at least **3 characters**.

If the username does not meet the requirement, the system displays an appropriate error message.

### 🔎 Duplicate Username Checking

Before creating a new account, the program checks `users.txt` using the `usernameExists()` function.

If the username is already registered, the system stops the registration process and displays an error message.

### 🔐 Password Validation

The program checks the password before storing it.

A password must contain at least **6 characters**.

If the password is too short, the system displays an appropriate error message.

### 🔒 Password Hashing and Storage

Before a password is stored, the program processes it through the `hashPassword()` function.

The stored file contains the username together with the resulting password hash instead of the original password.

The credentials are stored in:

```text
users.txt
```

### 🔑 Login Verification

The `loginUser()` function:

1. Accepts the username.
2. Accepts the password.
3. Hashes the entered password using the same hashing function.
4. Reads stored usernames and password hashes from `users.txt`.
5. Compares the entered username and generated password hash with the stored values.
6. Verifies the user's identity.
7. Displays a login success or error message.

### 💬 Success and Error Messages

The system provides appropriate feedback for different situations, including:

* Successful registration
* Successful login
* Duplicate username
* Invalid username
* Invalid password
* Invalid username or password
* File opening errors
* No registered users found

## 🧩 Functions Used

### `hashPassword()`

Processes the entered password and returns a hash value for storage and verification.

### `usernameExists()`

Reads the credential file and checks whether a username already exists.

### `registerUser()`

Handles the complete registration process, including:

* Username input
* Username validation
* Duplicate username checking
* Password input
* Password validation
* Password hashing
* Credential storage
* Registration result messages

### `loginUser()`

Handles the login process, including:

* Username input
* Password input
* Password hashing
* Reading stored credentials
* Credential comparison
* User identity verification
* Login result messages

### `main()`

Controls the program menu and calls the registration and login functions according to the user's choice.

## 🖥️ Program Menu

```text
====================================
     LOGIN & REGISTRATION SYSTEM
====================================
1. Register
2. Login
3. Exit
------------------------------------
Enter your choice:
```

## 🔄 Program Workflow

### Registration Flow

```text
Username Input
      ↓
Username Validation
      ↓
Duplicate Username Check
      ↓
Password Input
      ↓
Password Validation
      ↓
Password Hashing
      ↓
Store Username + Hash in users.txt
      ↓
Registration Result
```

### Login Flow

```text
Username Input
      ↓
Password Input
      ↓
Hash Entered Password
      ↓
Read Stored Credentials
      ↓
Compare Username + Password Hash
      ↓
Login Result
```

## 🧪 Testing Performed

The program was tested for the following scenarios:

* Successful user registration
* Duplicate username detection
* Invalid username input
* Invalid password input
* Successful login with correct credentials
* Invalid login with incorrect credentials
* Credential file creation and storage

## 📂 Project Files

### `Login_Registration.cpp`

The complete C++ source code containing:

* Password hashing
* Registration
* Login
* Username validation
* Duplicate username checking
* Password validation
* File handling
* Credential verification
* Menu system

### `README.md`

Project documentation describing the system, its features, workflow, functions, testing, and implementation.

## 🛠️ Technologies and Concepts Used

* C++
* File Handling
* Functions
* Strings
* Input Validation
* Loops
* Conditional Statements
* Password Hashing
* Standard C++ Library

## 🎥 Project Demonstration

The project demonstration shows the working Login and Registration System, including:

* User registration
* Duplicate username checking
* Username validation
* Password validation
* Successful login
* Invalid login handling
* File-based credential storage

## 📌 Internship Information

**Program:** CodeAlpha C++ Programming Internship
**Project:** Login and Registration System

## ✅ Project Status

**Completed**

The Login and Registration System has been implemented and tested according to the specified project requirements.
