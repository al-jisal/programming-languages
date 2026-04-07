/**
 * File: linkedlist.c -- contains the implementations of the declarations in linkedlist.h
 * 
 * Author: Desmond Frimpong
 * Project: 05
 * Date: April 9, 2026
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_linkedlist.h"

LinkedList * ll_create() {
    LinkedList * ll = ( LinkedList * ) malloc(sizeof(LinkedList));
    if ( ll == NULL ) return NULL;

    ll->head = NULL;
    ll->tail = NULL;

    return ll;
};

void ll_push(LinkedList *l, void *data) {
    if ( l == NULL ) return;

    Node * node = ( Node * ) malloc( sizeof( Node ) );
    if ( node == NULL ) return;
    node->data = data;
    node->next = l->head;
    node->prev = NULL;

    if( l->head != NULL ){
        l->head->prev = node;
    } else{
        l->tail = node;
    }

    l->head = node;
};

void *ll_pop(LinkedList *l) {
    if ( l == NULL || l->head == NULL) return NULL;

    Node * node = l->head;
    void * data = node->data;

    l->head = node->next;

    if( l->head != NULL ) {
        l->head->prev = NULL;
    } else{
        l->tail = NULL;
    }

    free( node );
    return data;
};

void ll_append(LinkedList *l, void *data) {
    if( l == NULL) return;

    Node * node = (Node *) malloc( sizeof( Node ) );
    if( node == NULL ) return;
    node->data = data;
    node->next = NULL;
    node->prev = l->tail;

    if( l->tail != NULL ) {
        l->tail->next = node;
    } else{
        l->head = node;
    }

    l->tail = node;
};

void ll_map(LinkedList *l, void (*mapfunc)(void *)) {
    if( l == NULL || mapfunc == NULL ) return;

    Node * node = l->head;
    while( node != NULL) {
        mapfunc(node->data);
        node = node->next;
    }
};