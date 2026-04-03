/**
 * File: task_3.yy -- replaces all single digits with their english equivalent.
 *                    replaces 10 with ten and all cat(s) with lion(s).
 *                    avoids replacement when targets are part of longer words
 * Author: Desmond Frimpong
 * Project: 02
 * Date: February 26, 2026
*/

%{
#include <stdio.h>
#include <ctype.h>
%}
%option caseless

LETTER  [a-zA-Z]
DIGIT   [0-9]
BOUND  (^|[^a-zA-Z0-9])


%%

{BOUND}cat[s]?/{BOUND}    {
    if (!isalpha(yytext[0]))
        putchar(yytext[0]);
    if (yytext[yyleng - 1] == 's'){
        printf("lions");
    } else {
        printf("lion");
    }
}

{BOUND}10/{BOUND}   {
    if (!isdigit(yytext[0]))
        putchar(yytext[0]);
    printf("ten");
}

{BOUND}{DIGIT}/{BOUND}  {
    if (!isdigit(yytext[0]))
        putchar(yytext[0]);

    switch ( yytext[yyleng - 1] ) {
        case '0': printf("zero"); break;
        case '1': printf("one"); break;
        case '2': printf("two"); break;
        case '3': printf("three"); break;
        case '4': printf("four"); break;
        case '5': printf("five"); break;
        case '6': printf("six"); break;
        case '7': printf("seven"); break;
        case '8': printf("eight"); break;
        case '9': printf("nine"); break;
    }
}

.|\n  putchar(yytext[0]);

%%

int main(){
    yylex();

    return 0;
}