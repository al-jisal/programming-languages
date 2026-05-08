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
#include <fenv.h>

void handler(int signal)
{
    printf("Handling division by zero\n");
    exit(1);
}

int main()
{

    signal(SIGFPE, handler);

    raise(SIGFPE);

    // Well I tried
    int *zero = malloc(sizeof(int));
    *zero = 0;
    scanf("%d", zero);
    printf("%d\n", *zero);
    int value = 5.66 / *zero;
    printf("Dividing %d by zero\n", value);
    return 0;
}