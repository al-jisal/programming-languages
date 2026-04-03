/**
 * File: fileCopier.c -- copies text stream from keyboard and
 *                       displays them in the terminal
 * Author: Desmond Frimpong
 * Date: February 9, 2026
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int c;

    // EOF means End Of Line. It's ctrl + D on the keyboard
    printf("EOF has %d as its value\n", EOF);
    while ((c = getchar()) != EOF){
        putchar(c);
    }
    
    return 0;
}