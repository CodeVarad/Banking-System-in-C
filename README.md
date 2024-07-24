# Banking System in C

## Overview

This project is a basic banking system implemented in C. It allows users to create accounts, deposit and withdraw money, and check their account balance. The system stores account details in a text file and includes validation to handle duplicate accounts and ensure correct credentials for transactions.

## How to Use

This project was developed using Visual Studio Code with a MinGW environment setup. Depending on your development environment, you may or may not encounter issues during compilation. 

### Compilation and Execution

1. **Compile the Project**:
   - Open the terminal in VSCode or use your preferred command line tool.
   - Open the project File.

2. **Run the Executable**:
   - run the main.C file though CodeRunner extention in VScode.

3. **Follow On-Screen Instructions**:
   - The program will display a menu with options. Follow the prompts to create an account, deposit or withdraw money, or check your balance.



## Features

- **Create Account**: Allows users to create a new account with a unique account number, name, social number, and password.
- **Deposit Amount**: Enables users to deposit money into their account.
- **Withdraw Amount**: Allows users to withdraw money from their account, with checks for sufficient balance.
- **Balance Enquiry**: Lets users check their current account balance.

## File Structure

- `banking_system.c`: Main source file containing the implementation of the banking system.
- `accounts.txt`: File where account details are stored (created automatically).
- `README.md`: This file, containing project details and instructions.

## Functions

### `createAccount()`

- **Purpose**: Creates a new account for the user.
- **Features**:
  - Prompts the user for their name, social number, and password.
  - Generates a unique account number.
  - Validates if an account with the same name and social number already exists.
  - Stores account details in `accounts.txt`.

### `depositAmount()`

- **Purpose**: Deposits a specified amount into the user's account.
- **Features**:
  - Prompts the user for their account number and deposit amount.
  - Validates the account number and updates the balance.
  - Ensures the file is correctly updated with the new balance.

### `withdrawAmount()`

- **Purpose**: Withdraws a specified amount from the user's account.
- **Features**:
  - Prompts the user for their account number, password, and withdrawal amount.
  - Validates the account number and password.
  - Checks if there is sufficient balance before processing the withdrawal.
  -  Updates the account balance and file if successful.

### `balanceEnquiry()`

- **Purpose**: Displays the current balance of the user's account.
- **Features**:
  - Prompts the user for their account number and password.
  - Validates the credentials and retrieves the current balance.
  - Displays an error message if the credentials are incorrect.


 
