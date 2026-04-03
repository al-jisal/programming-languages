/**
 * Filename: cstk.h -- contains the necessary structures and declarations of
 *                      the basic functions of a stack
 * Author: Desmond Frimpong
 * Project: 03
 * Date: March 12, 2026
*/

typedef struct Stack
{
    int *data;      // this is a pointer to the start of the data for the stack
    int *top;       // this will point to the next place to insert in the stack
    int capacity;   // this is the maximal size of the stack
} Stack;

// creates a Stack with a maximal capacity specified by the int value
Stack *stk_create(int);

// returns 1 if the given Stack is empty, otherwise 0
int stk_empty(Stack *);

// returns 1 if the given Stack is full, otherwise 0
int stk_full(Stack *);

// adds a new value to the top of the Stack if there's space.
// If there's no space, print out a warning but does nothing
void stk_push(Stack *, int);

// returns the value on the top of the Stack if such a value exists.
// otherwise. prints out a warning and returns 0
int stk_peek(Stack *);

// removes and returns the value on the top of the stack if such a value exists.
// otherwise, prints out a warning and returns 0
int stk_pop(Stack *);

// prints out the list in the reverse order (LILO) if the int value is 1.
// otherwise, prints out in the original order (LIFO)
void stk_display(Stack *, int);

// frees up the memory
void stk_destroy (Stack *);

// copies the contents into another Stack of the same maximal size and returns it.
Stack *stk_copy(Stack *);