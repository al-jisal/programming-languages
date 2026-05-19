/**
 * File: task_2b.c -- This program handles floating point exception
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigfpe(int sig) {
    (void)sig;
    printf("Caught SIGFPE: floating point/arithmetic exception handled.\n");
    printf("Exiting safely after handling the signal.\n");
    exit(EXIT_FAILURE);
}

int main(void) {
    signal(SIGFPE, handle_sigfpe);

    printf("About to trigger SIGFPE...\n");

    raise(SIGFPE);

    printf("This line should not print.\n");

    return 0;
}