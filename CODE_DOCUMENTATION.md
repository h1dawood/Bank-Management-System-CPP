# 📘 Code Documentation: Bank Management System

This document provides a detailed technical overview of the source code, including data structures, function logic, and file handling mechanisms used in the C++ Bank Management System.

## 1. Data Structures

The system uses a single C++ structure to represent a bank customer.

### `struct Account`
This structure holds all state information for a specific user.

| Field | Type | Description |
| :--- | :--- | :--- |
| **`id`** | `int` | Unique identifier (e.g., 1001). Auto-generated. |
| **`name`** | `string` | Customer's name (No spaces allowed in MVP file parsing). |
| **`phone`** | `string` | Contact number. |
| **`password`** | `string` | Security credential for login and withdrawals. |
| **`balance`** | `double` | Current funds available. |
| **`logs`** | `vector<string>` | A dynamic list of transaction history (Session-based). |

---

## 2. Global Variables & Constants

To maintain data in memory during runtime, the following global containers are used:

```cpp
vector<Account> accounts;      // The runtime database acting as a dynamic array.
const string FILENAME = "bank_data.txt"; // The path to the persistence file.
```

---

## 3. Function Reference

### 🛠 Helper & File I/O Functions

#### `void loadData()`
*   **Purpose:** Initializes the system state at startup.
*   **Logic:** Opens `bank_data.txt`. Reads data line-by-line using the `ifstream` extraction operator. Populates the `accounts` vector.
*   **Note:** If the file does not exist (first run), the vector remains empty.

#### `void saveData()`
*   **Purpose:** Persists data to the hard drive.
*   **Logic:** Opens `bank_data.txt` in overwrite mode (`ofstream`). Iterates through the `accounts` vector and writes fields separated by spaces.
*   **Format:** `ID Name Phone Password Balance`

#### `int findAccountIndex(int id)`
*   **Purpose:** Performs a Linear Search to find a user.
*   **Input:** `id` (The Account Number).
*   **Output:** Returns the **index** of the account in the vector if found, or `-1` if not found.

---

### 👨‍💼 Admin Functions

#### `void createAccount()`
*   **Logic:**
    1.  Determines the new ID: `(Last_ID + 1)` or `1001` if the vector is empty.
    2.  Collects user input (Name, Phone, Password).
    3.  Initializes balance to `0.0`.
    4.  Pushes the new struct into the `accounts` vector.
    5.  Calls `saveData()` immediately.

#### `void displayAllAccounts()`
*   **Logic:** Iterates through the vector and uses `<iomanip>` (`setw`, `left`) to print a formatted table of all users. Passwords are excluded for security.

#### `void searchAccount()`
*   **Logic:** Prompts for an ID, calls `findAccountIndex`, and displays the specific details of that single account if found.

---

### 👤 User Transaction Functions

#### `void userMenu(int index)`
*   **Purpose:** The main loop for a logged-in user.
*   **Logic:** Receives the `index` of the logged-in user. Displays a sub-menu (Deposit, Withdraw, Transfer, Logs) and loops until "Logout" is selected.

#### `void deposit(int index)`
*   **Logic:** Adds input amount to `accounts[index].balance` and adds a string record to `logs`.

#### `void withdraw(int index)`
*   **Logic:**
    1.  Checks if `Amount <= Balance`.
    2.  **Security:** Prompts user to re-enter their password.
    3.  If successful, deducts amount and updates `logs`.

#### `void transfer(int index)`
*   **Logic:**
    1.  **Validation:** Checks if Receiver ID exists and if Sender has sufficient funds.
    2.  **Self-Check:** Prevents transferring money to oneself.
    3.  **Confirmation:** Displays Receiver's Name and asks for `(y/n)` confirmation.
    4.  **Execution:** Atomic update—deducts from Sender and adds to Receiver.

#### `void showLogs(int index)`
*   **Logic:** Iterates through the `accounts[index].logs` vector and prints the history of the current session.

---

## 4. Main Execution Flow (`int main`)

1.  **Initialization:** Calls `loadData()` to populate memory.
2.  **Main Loop:** A `while(true)` loop displays the Main Menu.
3.  **Authentication:**
    *   Option 4 (Login) asks for ID and Password.
    *   If matched, control is passed to `userMenu()`.
4.  **Termination:** Option 5 calls `saveData()` to write changes to disk and then returns `0` to close the program.

---

## 5. File Storage Format

The `bank_data.txt` file is stored in plain text. Each line represents one account.

**Example Data:**
```text
1001 Ahmed 050123456 pass123 500.50
1002 Sara 050998877 myPass 1200.00
```

---

## 6. Known Limitations (MVP)

1.  **String Parsing:** Because the file loader uses standard `cin >>` logic, names in the text file cannot contain spaces (e.g., use "Ali_Hassan", not "Ali Hassan").
2.  **Log Persistence:** Transaction logs are stored in runtime memory (`vector`). While account balances are saved to the file, the history logs are reset when the program is closed.
3.  **Concurrency:** This is a single-threaded application suitable for one user at a time.
