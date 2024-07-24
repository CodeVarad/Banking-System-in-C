//Banking System in C language
//Author: CodeVarad  
//link : https://github.com/CodeVarad

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


void createaccount();
void depositamount();
void withdrawamount();
void balancecheck();

struct Account {
    int accno;
    char name[30]; 
    char sno[30];  //social number
    char pass[30];
    int bal;
    int depamount;
    int withamount;
    int found = 0;
} account;

int main() {
    int var;
    printf("Welcome to CodeVarad Banking Services. \n");
    printf("Please select a option from below. \n");
    printf("1. Create Account \n");
    printf("2. Deposit Amount \n");
    printf("3. Withdraw Amount \n");
    printf("4. Check Balance \n");
    printf("5. Exit \n");
    scanf("%d", &var);

    switch (var) {
        case 1:
            createaccount();
            break;

        case 2:
            depositamount();
            break;

        case 3:
            withdrawamount();
            break;

        case 4:
            balancecheck();
            break;

        case 5:
            printf("Thanks for using CodeVarad Banking Services!");
            return 0;
    }

    return 0;
}


void createaccount() {
    FILE *fileptr;
    char line[1000];


    fileptr = fopen("accounts.txt", "r");
    if (!fileptr) {
        fileptr = fopen("accounts.txt", "w");
        if (!fileptr) {
            fprintf(stderr, "There was an error creating the file.\n");
            return;
        }
        fclose(fileptr);
        fileptr = fopen("accounts.txt", "r");
    }
 
    printf("Enter your name: \n");
    scanf("%s", account.name);
    printf("Enter your Social Number: \n");
    scanf("%s", account.sno);

    while (fgets(line, sizeof(line), fileptr)) {
        char filename[30], filesno[30];
        sscanf(line, "%*d|%30[^|]|%30[^|]|%*[^|]|%*d", filename, filesno);  

        /**
         This is string format which specifies how the string input should be parsed.
         '[^|]':- Here this means that it will read data other than '|'.
         %30 is the max characters in string.
          */

        if (strcmp(filename, account.name) == 0 && strcmp(filesno, account.sno) == 0) {
            account.found = 1;
            break;
        }
    }

    fclose(fileptr);

    if (account.found) {
        printf("An account with this name and social number already exists.\n");
        return;
    }

    printf("Enter a Password for your account: \n");
    scanf("%30s", account.pass);

    srand(time(NULL));
    account.accno = 1000000000 + rand() % 9000000000;
   
    fileptr = fopen("accounts.txt", "a");
    if (!fileptr) {
        fprintf(stderr, "There was an error opening file.\n");
        return;
    }

    printf("Your account number is %d \n", account.accno);

     account.bal = 0;

    fprintf(fileptr, "%d|%s|%s|%s|%d\n", account.accno, account.name, account.sno, account.pass, account.bal);
    fclose(fileptr);
}

void depositamount() {
    float amount;
    char line[1000];
    FILE *fileptr, *tempfileptr;
    

    printf("Enter your account number: \n");
    scanf("%d", &account.accno);

    printf("Enter the amount to deposit: \n");
    scanf("%f", &amount);

    
    fileptr = fopen("accounts.txt", "r");
    if (!fileptr) {
        printf("Error opening file. Cannot deposit amount.\n");
        return;
    }

    tempfileptr = fopen("temp_accounts.txt", "w");
    if (!tempfileptr) {
        printf("Error opening temporary file.\n");
        fclose(fileptr);
        return;
    }

    while (fgets(line, sizeof(line), fileptr)) {
        int fileaccno;
        char filename[30], filesno[30], filepass[30];
        int filebal;
        
        sscanf(line, "%d|%30[^|]|%30[^|]|%30[^|]|%d", &fileaccno, filename, filesno, filepass, &filebal);
 
        if (fileaccno == account.accno) {
            account.found = 1;
            filebal = filebal + amount;
            fprintf(tempfileptr, "%d|%s|%s|%s|%d \n", fileaccno, filename, filesno, filepass, filebal);
        } else {
            fprintf(tempfileptr, "%s", line);
        }
    }

    fclose(fileptr);
    fclose(tempfileptr);

    if (!account.found) {
        printf("Couldn't find any account associated with the above number. \n");
    } else {
        remove("accounts.txt");
        rename("temp_accounts.txt", "accounts.txt");
        printf("Amount deposited successfully.\n");
    }
}


void withdrawamount() {
    float amount;
    char line[1000];
    FILE *fileptr, *tempfileptr;
    
    printf("Enter your account number: ");
    scanf("%d", &account.accno);
    printf("Enter your password: ");
    scanf("%s", account.pass);

    fileptr = fopen("accounts.txt", "r");
    if (!fileptr) {
        printf("Error opening file. Cannot withdraw amount.\n");
        return;
    }

    tempfileptr = fopen("temp_accounts.txt", "w");
    if (!tempfileptr) {
        printf("Error opening temporary file.\n");
        fclose(fileptr);
        return;
    }

    while (fgets(line, sizeof(line), fileptr)) {
        int fileaccno, filebal;
        char filename[30], filesno[30], filepass[30];
        
        sscanf(line, "%d|%30[^|]|%30[^|]|%30[^|]|%d", &fileaccno, filename, filesno, filepass, &filebal);

        if (fileaccno == account.accno && strcmp(filepass, account.pass) == 0) {
            account.found = 1;
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amount);

            if (filebal >= amount) {
                filebal -= amount;
                fprintf(tempfileptr, "%d|%s|%s|%s|%d\n", fileaccno, filename, filesno, filepass, filebal);
                printf("Withdrawal has been done successfully. Your new balance is %d.\n", filebal);
            } else {
                
                printf("The Balance is Insufficient.\n");
                fprintf(tempfileptr, "%s", line);
            }
        } else {
            fprintf(tempfileptr, "%s", line);
        }
    }

    fclose(fileptr);
    fclose(tempfileptr);
 
    if (!account.found) {
        printf("Invalid account number or password.\n");  
        remove("temp_accounts.txt");
    } else {
        remove("accounts.txt");
        rename("temp_accounts.txt", "accounts.txt");
    }
}

void balancecheck() {

    char line[100];
    FILE *fileptr;

    printf("Enter your account number: ");
    scanf("%d", &account.accno);
    printf("Enter your password: ");
    scanf("%s", &account.pass);

    fileptr = fopen("accounts.txt", "r");
    if (!fileptr) {
        printf("There was an error opening the file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fileptr)) {
        int fileaccno, filebal;
        char filename[30], filesno[30], filepass[30];
        
        sscanf(line, "%d|%30[^|]|%30[^|]|%30[^|]|%d", &fileaccno, filename, filesno, filepass, &filebal);

        if (fileaccno == account.accno && strcmp(filepass, account.pass) == 0) {
            account.found = 1;
            printf("Balance for account number %d is %d.\n", fileaccno, filebal);
            break;
        }
    }
    fclose(fileptr);
    if (!account.found) {
        printf("The account number or password is Invalid.\n");
    }
}

