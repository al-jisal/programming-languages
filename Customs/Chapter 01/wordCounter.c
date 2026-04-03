/**
 * File: wordCounter.c -- counts the number of words from an input text stream
 * Author: Desmond Frimpong
 * Date: February 9, 2026
 */

#include <stdio.h>
#include <stdlib.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main(int argc, char *argv[]){
    int c, nl, nw, nc, state;

    state = OUT; 
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF){
        ++nc;
        if (c == '\n'){
            ++nl;
        }
        if (c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
        }
        else if (state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("\nlines: %d\twords: %d\tcharacters: %d", nl, nw, nc);

    return 0;
}