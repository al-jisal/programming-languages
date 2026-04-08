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

// test function for the various linked list functions
int main(int argc, char *argv[]) {
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

    // *target = 11;
    // a = ll_find(l, target, compInt);
    // if (a != NULL)
    //     printf("\nFound: %d\n", *a);
    // else
    //     printf("\nNo instance of %d\n", *target);

    // printf("\nAfter removals\n");
    // ll_map(l, printInt);

//     // testing pushing data
//     ll_push(l, target);

//     printf("\nAfter push\n");
//     ll_map(l, printInt);

//     // test clearing
//     ll_clear(l, free);

//     printf("\nAfter clear\n");
//     ll_map(l, printInt);

//     // rebuild and test append and pop
//     for (i = 0; i < 5; i++) {
//         a = malloc(sizeof(int));
//         *a = i;
//         ll_append(l, a);
//     }

//     printf("\nAfter appending\n");
//     ll_map(l, printInt);

//     a = ll_pop(l);
//     printf("\npopped: %d\n", *a);
//     free(a);

//     a = ll_pop(l);
//     printf("popped: %d\n", *a);
//     free(a);

//     printf("\nAfter popping\n");
//     ll_map(l, printInt);

//     printf("\nList size: %d\n", ll_size(l));

//     return (0);
}