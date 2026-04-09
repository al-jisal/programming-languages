/*
        Stephanie Taylor
        CS333
        Linked list test function
        gcc -o clltest clltest.c my_linkedlist.c
        
        The output should be
        
After initialization
value: 0
value: 2
value: 4
value: 6
value: 8
value: 10
value: 12
value: 14
value: 16
value: 18

After squaring
value: 0
value: 4
value: 16
value: 36
value: 64
value: 100
value: 144
value: 196
value: 256
value: 324

removed: 16

No instance of 16

No instance of 11

After removals
value: 0
value: 4
value: 36
value: 64
value: 100
value: 144
value: 196
value: 256
value: 324

After push
value: 11
value: 0
value: 4
value: 36
value: 64
value: 100
value: 144
value: 196
value: 256
value: 324

After clear

After appending
value: 0
value: 1
value: 2
value: 3
value: 4

popped: 0
popped: 1

After popping
value: 2
value: 3
value: 4

List size: 3        
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_linkedlist.h"

// function that prints an integer
void printInt(void *i) {
    int *a = (int *)i;

    printf("value: %d\n", *a);
}

// function that squares an integer
void squareInt(void *i) {
    int *a = (int *)i;

    *a = *a * *a;
}

// function that compares two integers and returns 0 if they are equal
int compInt(void *i, void *j) {
    int *a = (int *)i;
    int *b = (int *)j;

    return (*a - *b);
}

// function that prints a string
void printStr(void *s) {
    char *str = (char *)s;
    printf("value: %s\n", str);
}

// function that converts a string to uppercase
void upperStr(void *s) {
    char * str = (char *) s;
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

// function that compares two strings
int compStr(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

// test function for the various linked list functions
int main(int argc, char *argv[]) {
    printf("---------------- INTEGER TESTS ----------------\n");
    LinkedList *l;
    int *a;
    int *target;
    int i;

    // create a list
    l = ll_create();

    // append data to the list
    for (i = 0; i < 20; i += 2) {
        a = malloc(sizeof(int));
        *a = i;
        ll_append(l, a);
    }

    // printing the list and testing map
    printf("After initialization\n");
    ll_map(l, printInt);

    ll_map(l, squareInt);

    printf("\nAfter squaring\n");
    ll_map(l, printInt);

    // testing removing data
    target = malloc(sizeof(int));

    *target = 16;
    a = ll_remove(l, target, compInt);
    if (a != NULL)
        printf("\nremoved: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);

    a = ll_remove(l, target, compInt);
    if (a != NULL)
        printf("\nremoved: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);

    *target = 11;
    a = ll_find(l, target, compInt);
    if (a != NULL)
        printf("\nFound: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);

    printf("\nAfter removals\n");
    ll_map(l, printInt);

    // testing pushing data
    ll_push(l, target);

    printf("\nAfter push\n");
    ll_map(l, printInt);

    // test clearing
    ll_clear(l, free);

    printf("\nAfter clear\n");
    ll_map(l, printInt);

    // rebuild and test append and pop
    for (i = 0; i < 5; i++) {
        a = malloc(sizeof(int));
        *a = i;
        ll_append(l, a);
    }

    printf("\nAfter appending\n");
    ll_map(l, printInt);

    a = ll_pop(l);
    printf("\npopped: %d\n", *a);
    free(a);

    a = ll_pop(l);
    printf("popped: %d\n", *a);
    free(a);

    printf("\nAfter popping\n");
    ll_map(l, printInt);

    printf("\nList size: %d\n", ll_size(l));

    printf("\n---------------- STRING TESTS ----------------");
    LinkedList *slist = ll_create();
    char *words[] = {"apple", "banana", "mango", "pear", "grape"};
    char *wordTarget;
    char *removedWord;
    char *foundWord;

    for (i = 0; i < 5; i++) {
        char *copy = malloc(strlen(words[i]) + 1);
        strcpy(copy, words[i]);
        ll_append(slist, copy);
    }

    printf("\nAfter string initialization\n");
    ll_map(slist, printStr);

    ll_map(slist, upperStr);

    printf("\nAfter converting strings to uppercase\n");
    ll_map(slist, printStr);

    wordTarget = (char *) malloc(strlen("GRAPE") + 1);
    strcpy(wordTarget, "GRAPE");


    removedWord = ll_remove(slist, wordTarget, compStr);
    if (removedWord != NULL) {
        printf("\nremoved: %s\n", removedWord);
        free(removedWord);
    } else {
        printf("\nNo instance of %s\n", wordTarget);
    }

    removedWord = ll_remove(slist, wordTarget, compStr);
    if (removedWord != NULL) {
        printf("\nremoved: %s\n", removedWord);
        free(removedWord);
    } else {
        printf("\nNo instance of %s\n", wordTarget);
    }

    foundWord = ll_find(slist, wordTarget, compStr);
    if (foundWord != NULL)
        printf("\nFound: %s\n", foundWord);
    else
        printf("\nNo instance of %s\n", wordTarget);

    free(wordTarget);

    printf("\nAfter string removal\n");
    ll_map(slist, printStr);

    char *newWord = malloc(strlen("coconunt") + 1);
    strcpy(newWord, "coconunt");
    ll_push(slist, newWord);

    printf("\nAfter string push\n");
    ll_map(slist, printStr);

    char *poppedWord = ll_pop(slist);
    if (poppedWord != NULL) {
        printf("\npopped: %s\n", poppedWord);
        free(poppedWord);
    }

    printf("\nAfter popping a string\n");
    ll_map(slist, printStr);

    printf("\nString list size: %d\n", ll_size(slist));

    ll_clear(slist, free);
    free(slist);

    return (0);
}