/**
 * File: task_2.yy -- counts number of rows, characters, and vowels
 *
 * Author: Desmond Frimpong
 * Project: 02
 * Date: February 26, 2026
*/
 
    int num_rows = 0, num_chars = 0, num_vowels = 0;

%%

\n  {
    ++num_rows;
    ++num_chars;
}

(?i:[aeiou]) ++num_vowels;

.   ++num_chars;

%%

int main() {
    yylex();
    printf("number of rows = %d,\n"
           "number of characters = %d,\n"
           "number of vowels = %d",
            num_rows, num_chars, num_vowels);
}