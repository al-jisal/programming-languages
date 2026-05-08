/**
 * File: task_2c.c -- This program handles a segmentation fault error
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
    printf("Handling seg fault error! \n");
    exit(1);
    return;
}

int main()
{
    signal(SIGSEGV, handler);
    int *ptr = NULL;
    printf("This is a pointer: %d", *ptr);
    return 0;
}