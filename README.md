# 🏦 Bank Management System (C++ MVP)

A robust console-based banking application written in C++. This project demonstrates Object-Oriented Programming (structs), data management using Vectors, and persistent storage using File I/O.

## 🚀 Features

### 👨‍💼 Admin Features
*   **Create New Accounts:** Auto-generates unique Account IDs.
*   **Display All Customers:** View a formatted list of all registered users and their balances.
*   **Search Accounts:** Find specific account details using a unique Account ID.
*   **Data Persistence:** Automatically saves all user data to a text file (`bank_data.txt`) so records are not lost when the program closes.

### 👤 User Features
*   **Secure Login:** Access accounts using a unique ID and Password.
*   **Deposit Money:** Add funds to the account with immediate balance updates.
*   **Withdraw Money:** Secure withdrawal with password verification and balance checks.
*   **Money Transfer:** Send money to other accounts with validation and user confirmation.
*   **Transaction Logs:** View a history of session-based transactions (Deposits, Withdrawals, Transfers).

## 🛠️ Technology Stack
*   **Language:** C++ (Standard 11+)
*   **Storage:** File Handling (`fstream`) & `std::vector` for dynamic memory.
*   **Interface:** Console-based UI.
*   **Concepts Used:** Structures, Vectors, Loops, Switch-Case, Functions.

## ⚙️ How to Run

1.  **Clone the Repository**
    ```bash
    git clone https://github.com/h1dawood/Bank-Management-System-CPP.git
    ```
2.  **Compile the Code**
    You can use any C++ compiler (GCC, Clang, or MSVC).
    ```bash
    g++ main.cpp -o BankSystem
    ```
3.  **Run the Application**
    *   **Windows:**
        ```bash
        BankSystem.exe
        ```
    *   **Linux/Mac:**
        ```bash
        ./BankSystem
        ```

*Note: This project is optimized for Windows (uses `system("cls")` and `system("pause")`). If running on Linux/Mac, you may need to adjust these commands to `system("clear")`.*

## 📂 Project Structure

```text
Bank-Management-System-CPP/
│
├── main.cpp          # The complete source code
├── bank_data.txt     # Database file (Auto-generated upon first run)
└── README.md         # Documentation
