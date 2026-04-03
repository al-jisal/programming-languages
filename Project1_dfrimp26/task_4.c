/**
 * File: task_5.c -- constructs a struct data structure
 * Author: Desmond Frimpong
 * Date: February 19, 2026
 */

#include <stdio.h>
#include <stdlib.h>

/* this structure defines a student */
struct student {
    int id;
    char sex;
    float gpa;
    char major[4];
};

int main(int argc, char *argv[]){
    struct student dfrimp26 = { 0x21, 'M', 2.1, "ECE"};
    unsigned char *ptr = (unsigned char *) &dfrimp26;
   
    for (int i = 0; i < sizeof(struct student); ++i){
        printf("%2X\n", ptr[i]);
    }
    printf("\nsize of struct student: %lu", sizeof(dfrimp26));
    return 0;
}