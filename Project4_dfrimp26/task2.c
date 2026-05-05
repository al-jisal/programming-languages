/**
 * Filename: task2.c -- computes and returns the factorial value of an integer
 * 
 * Author: Desmond Frimpong
 * Project: 04
 * Date: March 20, 2026
*/
#include <stdio.h>
#include <stdlib.h>

int factorial( int n ){
    int result = 1;
    if ( n <= 1) return result;

    while( n > 1 ){
        result *= n;
        n -= 1;
    }
    return result;
}

int main( int argc, char *argv[] ){
    //command-line argument processing
    if( argc < 2 ){
        printf("enter the number whose factorial is to be computed! \n");
        return 1;
    }
    int N = atoi(argv[1]);

    int (* calc)(const int);
    calc = factorial;
    printf("the factorial of %d is: %d\n", N, calc(N));
    return 0;
}