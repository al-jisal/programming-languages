#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_linkedlist.h"

typedef struct {
    float height;
    float weight;
    char *name;
} Dog;

void clean_up_dog( void *data ) {
    Dog *d = (Dog *)data;
    free( d->name );
    free( d );
}

void print_dog( void *data ) {
    Dog *dog = (Dog *)data;
    printf( "%s weighs %0.2f lbs and is %0.2f inches tall\n", dog->name, dog->weight, dog->height );
}

// code that generates a linked list that you need to draw 
int main(int argc, char *argv[]) {
    LinkedList *the_list;

    // create a list
    the_list = ll_create();

    Dog *d = (Dog *)malloc( sizeof(Dog) );
    d->height = 11.2;
    d->weight = 33.4;
    d->name = (char *)malloc(7);
    strcpy( d->name, "Loosie" );
    
    ll_append( the_list, d );
    d = NULL;

    // Mark 1

    ll_map( the_list, print_dog );
        
    ll_clear(the_list, clean_up_dog);
    return 0;
}