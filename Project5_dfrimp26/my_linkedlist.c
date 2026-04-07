/**
 * File: linkedlist.c -- contains the implementations of the declarations in linkedlist.h
 * 
 * Author: Desmond Frimpong
 * Project: 05
 * Date: April 9, 2026
*/

#include <stdlib.h>
#include <stdio.h>
#include <linkedlist.h>

LinkedList * ll_create() {
    LinkedList * ll = ( LinkedList * ) malloc(sizeof(LinkedList));
    if ( ll == NULL ) return NULL;

    ll->head = ( Node * ) malloc( sizeof( Node ) );
    if ( ll->head == NULL ) {
        free( ll );
        return NULL;
    }

    ll->tail = ( Node * ) malloc( sizeof( Node ) );
    if ( ll->tail == NULL ) {
        free( ll );
        return NULL;
    }

    return ll;
};

void ll_push(LinkedList *l, void *data) {
    if ( l == NULL ) return NULL;

    Node * node = ( Node * ) malloc( sizeof( Node ) );
    if ( node == NULL ) return NULL;

    node->data = data;
    node->next = l->head;
    l->head->prev = node;

    l->head = node;
};

void *ll_pop(LinkedList *l) {
    if ( l == NULL ) return NULL;

    Node * node = l->head;
    l->head = node->next;
    l->head->prev = NULL;

    return node->data;
};

