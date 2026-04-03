/**
 * File: task_2.c -- shows where values are on the stack
 * Author: Desmond Frimpong
 * Date: February 19, 2026
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char star = '*';
    char first = 'a';
    char last = 'z';
    int room_temp = 32;
    float prime = 11.0;
    int age = 15;
    unsigned char *ptr;
    ptr = (unsigned char *)&ptr;

    printf("Index\tByte\n");
    for (int i = 0; i < 100; i++){
        printf("%d\t%2X\n", i, ptr[i]);
    }

    return 0;
}