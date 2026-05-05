/**
 * Filename: cstk2.c -- contains the implementations of the necessary structures
 *                      and declarations in cstk2.h     
 * Author: Desmond Frimpong
 * Project: 04
 * Date: March 20, 2026
*/

#include <stdlib.h>
#include <stdio.h>
#include "cstk2.h"

Stack *stk_create(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->data = (void **) malloc(capacity * sizeof(void *));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->top = stack->data;
    stack->capacity = capacity;

    return stack;
}

void stk_destroy(Stack *stack) {
    if (stack == NULL) return;

    free(stack->data);
    free(stack);
}

int stk_size(Stack *stack) {
    if( stack == NULL ) return -1;
    return stack->top - stack->data;
}

int stk_full(Stack *stack) {
    if (stack == NULL) return -1;

    if (stack->top == (stack->data + stack->capacity)) return 1;
    return 0;
}

int stk_empty(Stack *stack) {
    if (stack == NULL) return -1;

    if (stack->data == stack->top) return 1;
    return 0;
}

void stk_push(Stack *stack, void *value) {
    if (stack == NULL) return;

    if (stk_full(stack)){
        printf("No space on stack for item\n");
    } else {
        *stack->top = value;
        stack->top += 1;
    }
}

void *stk_peek(Stack *stack) {
    if (stack == NULL) return NULL;

    if (stk_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    } else {
        return *(stack->top - 1);
    }
}

void *stk_pop(Stack *stack) {
    if (stack == NULL) return NULL;

    if (stk_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    } else {
        stack->top -= 1;
        return *(stack->top);
    }
}

char *stk_toString(Stack *stack, char *(*toString)(void *)) {
    // Start with an initial capacity of 1024 characters
    int capacity = 1024;
    char *result = (char *)malloc(capacity * sizeof(char));

    result[0] = '\0'; 

    int length = 0; 

    for (void **current = stack->data; current < stack->top; current++) {
        char *itemString = toString(*current);
        int itemLength = strlen(itemString);

        // Check if we need to resize the buffer
        if (length + itemLength + 2 > capacity) { 
            while (length + itemLength + 2 > capacity) {
                capacity *= 2; // Double the capacity
            }

            // Reallocate with new capacity
            char *newResult = (char *)realloc(result, capacity * sizeof(char));
            if (newResult == NULL) {
                free(result); // Free original buffer
                free(itemString); // Free itemString
                return NULL;
            }
            result = newResult;
        }

        // Concatenate itemString to result
        strcat(result + length, itemString);
        length += itemLength;

        // adds the separator ", " to all items except the last
        if (current < stack->top - 1) {
            strcat(result + length, ", ");
            length += 2;
        }

        free(itemString); // Free temporary item string
    }

    return result;
}