/**
 * Filename: cstk.c -- contains the implementations of the necessary structures
 *                      and declarations in cstk.h     
 * Author: Desmond Frimpong
 * Project: 03
 * Date: March 12, 2026
*/

#include <stdlib.h>
#include <stdio.h>
#include "cstk.h"

Stack *stk_create(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->data = (int *) malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->top = stack->data;
    stack->capacity = capacity;

    return stack;
}

int stk_empty(Stack *stack) {
    if (stack == NULL) return -1;

    if (stack->data == stack->top) return 1;
    return 0;
}

int stk_full(Stack *stack) {
    if (stack == NULL) return -1;

    if (stack->top == (stack->data + stack->capacity)) return 1;
    return 0;
}

void stk_push(Stack *stack, int value) {
    if (stack == NULL) return;

    if (stk_full(stack)){
        printf("No space on stack for item\n");
    } else {
        *stack->top = value;
        stack->top += 1;
    }
}

int stk_peek(Stack *stack) {
    if (stack == NULL) return -1;

    if (stk_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    } else {
        return *(stack->top - 1);
    }
}

int stk_pop(Stack *stack) {
    if (stack == NULL) return -1;

    if (stk_empty(stack)) {
        printf("stack is empty\n");
        return 0;
    } else {
        int removed = *(stack->top - 1);
        stack->top -= 1;
        return removed;
    }
}

void stk_display(Stack *stack, int order) {
    if (stack == NULL) return;

    int size = stack->top - stack->data;

    if (order == 1){
        for (int i = 0; i < size; i++) {
            printf("%d,\t", stack->data[i]);
        }
    } else {
        for (int i = size - 1; i > -1; i--) {
            printf("%d,\t", stack->data[i]);
        }
    }
    printf("\n");
}

void stk_destroy(Stack *stack) {
    if (stack == NULL) return;

    free(stack->data);
    free(stack);
}

Stack *stk_copy(Stack *stack) {
    if (stack == NULL) return NULL;

    Stack *new_stack = (Stack *) malloc(sizeof(Stack));
    if (new_stack == NULL) return NULL;

    new_stack->data = (int *) malloc(stack->capacity * sizeof(int));
    if (new_stack->data == NULL){
        free(new_stack);
        return NULL;
    }

    int size = stack->top - stack->data;
    new_stack->top = new_stack->data + size;
    new_stack->capacity = stack->capacity;

    for (int i = 0; i < size; i++) {
        new_stack->data[i] = stack->data[i];
    }

    return new_stack;
}