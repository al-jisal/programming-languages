/**
 * Test code for Stack 
 *
 * Ying Li
 * 08/01/2016
 */

#include "cstk.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	Stack *s = stk_create(20);
	
	int i;
	for(i = 0; i < 10; i++) {
		stk_push(s, i+1);
	} 

	printf("s is at %p\n", &s);
	printf("s contains %p\n\n", s);
	printf("s->data is at %p\n", &s->data);
	printf("s->data contains %p\n\n", s->data);
	printf("s->top is at %p\n", &s->top);
	printf("s->top contains %p\n\n", s->top);
	printf("s->capacity is at %p\n", &s->capacity);
	printf("s->capacity contains %d\n\n", s->capacity);
    // Mark 1 (first memory picture)
	
	printf("The original list: ");
	stk_display(s, 0);
	
	printf("The reversed list: ");
	stk_display(s, 1);
	
	stk_destroy(s);
    // Mark 2 (first memory picture)
	printf("s is at %p\n", &s);
	printf("s contains %p\n\n", s);
	printf("s->data is at %p\n", &s->data);
	printf("s->data contains %p\n\n", s->data);
	printf("s->top is at %p\n", &s->top);
	printf("s->top contains %p\n\n", s->top);
	printf("s->capacity is at %p\n", &s->capacity);
	printf("s->capacity contains %d\n\n", s->capacity);
	
	return 0;
}
