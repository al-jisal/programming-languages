/**
 * File: tempConverter.c -- converts temperatures in Fahrenheit to Celsius
 * 
 * Author: Desmond Frimpong
 * Date: February 6, 2026
 */

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(int argc, char *argv[]){
    float fahr, celsius;
    // float lower, upper, step;

    // lower = 0;
    // upper = 300;
    // step = 20;
    fahr = LOWER;

    while (fahr <= UPPER){
        celsius = 5 * (fahr - 32) / 9;
        printf("%.2f\t%.2f\n", fahr, celsius);
        fahr += STEP;
    }

    return 0;
}

// int main(int argc, char *argv[]){
//     float fahr, celsius;

//     for (fahr = 0.0; fahr <= 300.0; fahr += 20.0){
//         celsius = (5.0/9.0) * (fahr - 32.0);
//         printf("%.2f\t%.2f\n", fahr, celsius);
//     }

//     return 0;
// }