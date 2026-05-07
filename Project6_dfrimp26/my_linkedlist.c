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
    ll->size = 0;

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
    l->size += 1;
};

void *ll_pop(LinkedList *l) {
    if ( l == NULL || l->head == NULL) return NULL;

    Node * node = l->head;
    void * data = node->data;

    l->head = node->next;
    l->size -= 1;

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
    l->size += 1;
};

void *ll_remove(LinkedList *l, void *target, int (*compfunc)(void *, void *)) {
    if( l == NULL || target == NULL || compfunc == NULL ) return NULL;

    Node * node = l->head;
    while (node != NULL) {
        if (compfunc(target, node->data) == 0) {
            void *data = node->data;

            if (node->prev != NULL) {
                node->prev->next = node->next;
            } else {
                l->head = node->next;   // removing head
            }

            if (node->next != NULL) {
                node->next->prev = node->prev;
            } else {
                l->tail = node->prev;   // removing tail
            }

            free(node);
            l->size -= 1;
            return data;
        }
        node = node->next;
    }


    return NULL;
};

void *ll_find(LinkedList *l, void *target, int (*compfunc)(void *, void *)) {
    if( l == NULL || target == NULL || compfunc == NULL ) return NULL;

    Node * node = l->head;
    while( node != NULL ) {
        if( compfunc(target, node->data ) == 0 ){
            return node->data;
        } else {
            node = node->next;
        }
    }

    return NULL;
};

int ll_size(LinkedList *l){
    if( l == NULL ) return -1;
    return l->size;
};

void ll_clear(LinkedList *l, void (*freefunc)(void *)) {
    if( l == NULL || freefunc == NULL) return;

    Node * node = l->head;

    while( node != NULL ){
        Node * next = node->next;
        freefunc( node->data ); 
        freefunc(node);
        node = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
};

void ll_map(LinkedList *l, void (*mapfunc)(void *)) {
    if( l == NULL || mapfunc == NULL ) return;

    Node * node = l->head;
    while( node != NULL) {
        mapfunc(node->data);
        node = node->next;
    }
};