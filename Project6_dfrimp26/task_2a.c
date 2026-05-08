/**
 * File: task_2a.c -- This program responds to ctrl + C interrupt
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signal)
{
    printf("\nInterrupted\n");
    exit(EXIT_SUCCESS);
    return;
}

int main()
{
    // SIGINT "program interrupt" signal, the signal is sent when the user type
    // INTR character, usually Ctrl +C
    signal(SIGINT, handler);

    while (1)
    {
        printf("I am an infinite loop");
    }

    return 0;
}