/**
 * File: hashtable.h -- contain the necessary structures and the declarations of 
 *                      the basic functions of a hash table
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H


typedef struct Counter {
    char *word;
    int count;
    bool isOccupied; // shows if the slot is occupied or not
} Counter;

typedef struct HashTable {
    Counter *table; // underlying array for hashtable
    int capacity;
    int size; // number of items stored in the table
} HashTable;


/**
 * @brief Initialize a hash table and returns it
 *
 */
HashTable *init_hash_table();

/**
 * @brief Stores words and their frequency in the hash table
 * @param word
 */
void ht_store_word(HashTable* ht, const char* word);

/**
 * @brief frees hash table
 */
void free_hash_table(HashTable *ht);

#endif