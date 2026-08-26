# C++ Bank Management System

A clean, modular, and menu-driven **Bank Management System** developed in **C++**. This project demonstrates core Object-Oriented Programming (OOP) concepts, file handling, input validation, string parsing, and data persistence using standard C++ libraries.

> **Note:** This is an **educational portfolio project** designed to illustrate software design fundamentals, data structures, and OOP paradigms in modern C++. It is not intended for real-world production financial transactions.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Concepts Used](#concepts-used)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [Data Storage](#data-storage)
- [How to Run](#how-to-run)
- [Usage & Menu Options](#usage--menu-options)
- [Sample Output](#sample-output)
- [Screenshots](#screenshots)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Learning Outcomes](#learning-outcomes)
- [License](#license)

---

## Overview

The **C++ Bank Management System** is a console-based application that simulates everyday banking operations including opening new accounts, depositing and withdrawing funds, searching account details, reviewing full transaction audit histories, and closing accounts. 

All account and transaction data are automatically persisted to local storage files (`accounts.txt` and `transactions.txt`), ensuring data remains available across program executions.

---

## Features

- **Create New Bank Accounts:** Collects account holder name, phone number, account type (`Savings` or `Current`), and initial deposit.
- **Automatic Account Number Generation:** Automatically assigns unique, sequential account numbers (starting from `1001`).
- **Display All Accounts:** Formats and lists all registered accounts with live balance figures.
- **Search Account:** Quickly retrieves and displays details for any existing account by account number.
- **Deposit Money:** Credits funds to an account with instant balance calculation and transaction logging.
- **Withdraw Money:** Validates account balance before deducting funds, preventing overdrafts and negative withdrawals.
- **Transaction History:** Displays a formatted chronological ledger of all deposits, withdrawals, and initial opening deposits with exact timestamps.
- **Delete Account:** Removes an account record after an interactive confirmation prompt (`Y/N`).
- **File-Based Persistence:** Automatically loads account data on startup and writes back changes to flat text files.
- **Defensive Input Handling:** Protects against invalid numeric entries, stream failures, and empty string inputs.

---

## Concepts Used

| Concept | Implementation in Code |
|---|---|
| **Classes & Objects** | Encapsulates banking entities (`BankAccount`) and operational logic (`BankSystem`) into self-contained classes. |
| **Encapsulation & Access Specifiers** | Data members (`accountNumber`, `balance`, etc.) are declared `private`, protected from direct external tampering, and accessed via `public` member functions and getters. |
| **Constructors** | Default and parameterized constructors initialize account objects with clean default states and custom parameters. |
| **STL Vector (`std::vector`)** | Dynamically stores and manages in-memory collections of `BankAccount` objects without fixed array size restrictions. |
| **File I/O (`std::ifstream` & `std::ofstream`)** | Implements persistent read/write workflows (`accounts.txt` and `transactions.txt`) using delimited parsing (`\|`). |
| **Input Validation & Stream Recovery** | Uses `cin.fail()`, `cin.clear()`, and `cin.ignore()` with `std::numeric_limits` to prevent infinite loops from invalid user inputs. |
| **String Manipulation & Parsing** | Utilizes `std::string`, `getline()`, `substr()`, `find()`, `stoi()`, and `stod()` to tokenize and deserialize persistent records. |
| **Formatted Console Output** | Employs `<iomanip>` manipulators (`std::setw`, `std::left`, `std::fixed`, `std::setprecision`) for clean, aligned tabular reporting. |
| **Date & Time Processing** | Leverages `<ctime>` (`time()`, `localtime()`, `strftime()`) to generate real-time timestamps (`YYYY-MM-DD HH:MM:SS`) for transaction logs. |
| **Menu-Driven Architecture** | Uses `do-while` loops, `switch-case` branches, and modular helper functions for an intuitive CLI experience. |

---

## Technologies Used

- **Language:** C++ (C++11 / C++17 / C++20 compatible)
- **Standard Library:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<limits>`, `<ctime>`
- **Compiler:** GCC / MinGW (`g++`) or MSVC / Clang
- **Development Environment:** Visual Studio Code / Terminal
- **Version Control:** Git & GitHub

---

## Project Structure

```text
C++-Bank-Management-System/
│
├── main.cpp                 # Main C++ source code containing BankAccount & BankSystem classes
├── README.md                # Comprehensive project documentation
├── .gitignore               # Excludes build binaries, IDE settings, and local runtime data
│
└── screenshots/             # Output preview captures of the application
    ├── main-menu.png
    ├── account-creation.png
    ├── deposit-withdrawal.png
    └── transaction-history.png
```

### Runtime Generated Files
When the program executes, it creates and manages two local text files in the working directory:
- `accounts.txt` — Stores account details formatted as `accountNumber|accountHolder|phoneNumber|accountType|balance`.
- `transactions.txt` — Stores transaction logs formatted as `timestamp|accountNumber|type|amount|balance`.

*(These files are excluded from git tracking via `.gitignore` to prevent local test data from polluting the repository.)*

---

## Data Storage

Data persistence in this project is implemented using flat-file text storage:

1. **`accounts.txt`:**
   - Updated whenever an account is created, modified (deposit/withdrawal), or deleted.
   - Example line: `1001|Israr Gabol|03001234567|Savings|15000.00`
2. **`transactions.txt`:**
   - Appended with an audit record whenever an initial deposit, deposit, or withdrawal occurs.
   - Example line: `2026-08-26 14:30:15|1001|Deposit|5000.00|15000.00`

> **Storage Architecture Note:** Flat-file storage is lightweight, portable, and requires zero external database installation, making it ideal for educational C++ projects.

---

## How to Run

### Prerequisites
- A standard C++ compiler supporting C++11 or higher (such as **MinGW / GCC `g++`**, **Clang**, or **MSVC**).
- **VS Code** (with the *C/C++* extension) or any standard terminal / command prompt.

---

### Step 1: Clone the Repository
```bash
git clone https://github.com/isrargabol/C--Bank-Management-System.git
cd C--Bank-Management-System
```

### Step 2: Compile the Source Code
Using the standard `g++` compiler:

```bash
g++ main.cpp -o BankManagementSystem -std=c++17
```

### Step 3: Run the Application

**On Windows:**
```bash
BankManagementSystem.exe
```

**On Linux / macOS:**
```bash
./BankManagementSystem
```

---

## Usage & Menu Options

Upon running the application, the interactive main menu is presented:

```text
=============================================
          BANK MANAGEMENT SYSTEM
=============================================
1. Create New Account
2. Display All Accounts
3. Search Account
4. Deposit Money
5. Withdraw Money
6. Transaction History
7. Delete Account
8. Exit
=============================================
Enter your choice: 
```

| Option | Action |
|---|---|
| `1` | Prompts for account holder details and initial balance, creates a new account, and assigns an ID. |
| `2` | Displays all registered bank accounts with current balances. |
| `3` | Searches and retrieves a specific account by its account number. |
| `4` | Deposits a specified sum into an existing account and updates records. |
| `5` | Withdraws funds after validating account balance sufficiency. |
| `6` | Displays the timestamped transaction log table for a given account. |
| `7` | Removes an account upon typing `Y` or `y` in the confirmation dialog. |
| `8` | Exits the application cleanly. |

---

## Sample Output

### 1. Creating an Account
```text
========== CREATE NEW ACCOUNT ==========
Enter account holder name: Israr Gabol
Enter phone number: 03001234567
Enter account type (Savings/Current): Savings
Enter initial deposit: Rs. 10000

Account created successfully!
Your Account Number is: 1001
```

### 2. Depositing Funds
```text
========== DEPOSIT MONEY ==========
Enter account number: 1001
Enter amount to deposit: Rs. 5000

Deposit successful.
New Balance: Rs. 15000.00
```

### 3. Withdrawing Funds
```text
========== WITHDRAW MONEY ==========
Enter account number: 1001
Current Balance: Rs. 15000.00
Enter amount to withdraw: Rs. 3000

Withdrawal successful.
Remaining Balance: Rs. 12000.00
```

### 4. Viewing Transaction History
```text
========== TRANSACTION HISTORY ==========
Enter account number: 1001

Date & Time         Type              Amount         Balance        
--------------------------------------------------------------------
2026-08-26 14:10:02 Initial Deposit   Rs. 10000.00   Rs. 10000.00   
2026-08-26 14:15:30 Deposit           Rs. 5000.00    Rs. 15000.00   
2026-08-26 14:20:11 Withdrawal        Rs. 3000.00    Rs. 12000.00   
```

### 5. Searching an Account
```text
========== SEARCH ACCOUNT ==========
Enter account number: 1001

---------------------------------------------
Account Number : 1001
Account Holder : Israr Gabol
Phone Number   : 03001234567
Account Type   : Savings
Balance        : Rs. 12000.00
---------------------------------------------
```

---

## Screenshots

### 1. Main Menu
<p align="center">
  <img src="https://raw.githubusercontent.com/isrargabol/C--Bank-Management-System/main/screenshots/main-menu.png" alt="Main Menu" width="800" />
</p>

### 2. Account Creation
<p align="center">
  <img src="https://raw.githubusercontent.com/isrargabol/C--Bank-Management-System/main/screenshots/account-creation.png" alt="Account Creation" width="800" />
</p>

### 3. Deposit & Withdrawal Operations
<p align="center">
  <img src="https://raw.githubusercontent.com/isrargabol/C--Bank-Management-System/main/screenshots/deposit-withdrawal.png" alt="Deposit and Withdrawal" width="800" />
</p>

### 4. Transaction History Audit Log
<p align="center">
  <img src="https://raw.githubusercontent.com/isrargabol/C--Bank-Management-System/main/screenshots/transaction-history.png" alt="Transaction History" width="800" />
</p>

---

## Limitations

As a student-level educational console application, the system has several intentional design boundaries:
- **Console Interface (CLI):** Does not feature a graphical UI (GUI) or web interface.
- **Local Flat-File Storage:** Uses plain text files (`accounts.txt`, `transactions.txt`) instead of an ACID-compliant SQL/NoSQL database server.
- **Single-User Scope:** Designed for single-session desktop execution without multi-threaded concurrency locking.
- **Basic Security:** Account numbers are accessible without hashed PIN/password authentication or encrypted storage.

---

## Future Improvements

Potential enhancements planned for future iterations:
- [ ] **Graphical User Interface (GUI):** Build a modern desktop frontend using **Qt** or **wxWidgets**.
- [ ] **Database Integration:** Migrate flat-file storage to **SQLite** or **PostgreSQL** for relational data integrity.
- [ ] **Authentication & Security:** Implement PIN/password protection with SHA-256 password hashing.
- [ ] **Inter-Account Transfers:** Enable direct fund transfers from one account number to another.
- [ ] **Role-Based Access Control:** Separate customer self-service actions from bank manager / admin privileges.
- [ ] **Export Statements:** Generate downloadable PDF / CSV account statements for specified date ranges.

---

## Learning Outcomes

Building this project reinforced core software engineering and C++ concepts:
- Designing modular, maintainable code using **Object-Oriented Programming (OOP)**.
- Managing heap/stack memory safely with modern C++ standard library containers (`std::vector`).
- Implementing resilient **file I/O parsing** and serialization logic.
- Handling defensive user input streams to prevent crash loops and malformed states.
- Structuring a clean, professional GitHub repository with clear documentation and build instructions.

---

## License

This project is licensed under the **MIT License** — feel free to use and adapt this code for educational and learning purposes.
