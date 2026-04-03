/**
 * File: encoder.yy -- that takes any character in a-z or A-Z and shifts it 13 spaces
 *                    
 * Author: Desmond Frimpong
 * Project: 02
 * Date: February 26, 2026
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shift = 13;        /* default ROT13 shift */
int rotate_digits = 0; /* digit rotation off by default */
int reverse_mode = 0;  /* reverse (decryption) off by default */
%}

%option noyywrap
%option 8bit

%%

[a-z]  {
    int s = shift;
    if (reverse_mode)
        s = 26 - shift;
    putchar((yytext[0] - 'a' + s) % 26 + 'a');
}

[A-Z]  {
    int s = shift;
    if (reverse_mode)
        s = 26 - shift;
    putchar((yytext[0] - 'A' + s) % 26 + 'A');
}

[0-9]  {
    if (rotate_digits) {
        int d_shift = 5;
        if (reverse_mode)
            d_shift = 10 - d_shift;
        putchar((yytext[0] - '0' + d_shift) % 10 + '0');
    } else {
        putchar(yytext[0]);
    }
}

    /* Pass through UTF-8 bytes unchanged */
[\200-\377]  {
    putchar(yytext[0]);
}

    /* Everything else */
.|\n  {
    putchar(yytext[0]);
}

%%

int main(int argc, char *argv[]) {

    /* Parse command line arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0)
            rotate_digits = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse_mode = 1;
        else
            shift = atoi(argv[i]) % 26;
    }

    yylex();
    return 0;
}