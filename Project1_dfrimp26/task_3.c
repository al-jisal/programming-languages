/**
 * File: task_3.c -- repeatedly allocates memory for a long time
 * Author: Desmond Frimpong
 * Date: February 19, 2026
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    unsigned char *some_memory;

    for (int i = 0; i < 1000000000; i++){
        some_memory = (unsigned char *) malloc(100 * sizeof(double));
        // free(some_memory);
    }

    return 0;
}