/**
 * File: task_4.yy -- implements a parser for Clite
 *                    
 * Author: Desmond Frimpong
 * Project: 02
 * Date: February 26, 2026
*/

%{
#include <stdio.h>
%}

%option noyywrap

INTEGER     [0-9]+
FLOAT       {INTEGER}\.{INTEGER}
IDENTIFIER  [A-Za-z_][A-Za-z0-9_]*
KEYWORD     if|else|while|for|int|float
COMPARISON  <=|>=|==|<|>
OPERATOR    [+\-*/]

%%

{KEYWORD}      printf("Keyword-%s\n", yytext);

{FLOAT}        printf("Float-%s\n", yytext);

{INTEGER}      printf("Integer-%s\n", yytext);

{COMPARISON}   printf("Comparison-%s\n", yytext);

{OPERATOR}     printf("Operator-%s\n", yytext);

"="            printf("Assignment\n");

"{"            printf("Open-bracket\n");
"}"            printf("Close-bracket\n");
"("            printf("Open-paren\n");
")"            printf("Close-paren\n");

{IDENTIFIER}   printf("Identifier-%s\n", yytext);

[ \t\n]+       ;

.              ;

%%

int main() {
    yylex();
    return 0;
}