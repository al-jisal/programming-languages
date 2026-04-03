/**
 * File: task_1.yy -- that takes any character in a-z or A-Z and shifts it 13 spaces
 *                    forward in the alphabet, with wraparound from z back to a
 * Author: Desmond Frimpong
 * Project: 02
 * Date: February 26, 2026
*/

%{
#include <stdio.h>
%}

%%

[a-z]  {
    putchar( (yytext[0] - 'a' + 13) % 26 + 'a' );
}

[A-Z] {
   putchar( (yytext[0] - 'A' + 13) % 26 + 'A' ); 
}

%%

int main(){
    yylex();

    return 0;
}