/**
 * @file BankExample.c
 * @author Max Bender
 * @date 2024-01-22
 * 
 * A ROBUST example to demonstrate need for care when managing strings in C.
 *
 * Modified by Desmond Frimpong 02/19/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This creates a definition for the struct Account.
 *
 * Note that balance (an int) is saved after name in memory.
 */
typedef struct Account {
    char name[50];    /* increased array size, allowing full name usage */
    int balance;
} Account;

int main(int arg, char *argv[]) {
    Account newAccount = {"", 0};
    printf("Please input your name for a new bank account: ");
    
    fgets(newAccount.name, sizeof(newAccount.name), stdin); /* reads input up to size of Account.name */
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0'; /* removes new line character if present */
    printf("Thank you %s, your new account has been initialized with balance %d.\n",
           newAccount.name, newAccount.balance);

    return 0;
}