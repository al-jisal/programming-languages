/**
 * File: hashtable.h -- contains the implementations of the declarations in hashtable.h
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

#define TABLE_SIZE 1024

/**
 * Hash function for the table
 */
unsigned int hash(const char *word)
{
    int length = strnlen(word, 100);
    unsigned int value = 0;
    for (int i = 0; i < length; i++)
    {
        value = value * 11 + word[i];
    }
    return value % TABLE_SIZE;
}

/**
 * Creates a hashtable
 */
HashTable *init_hash_table()
{
    HashTable *ht = malloc(sizeof(HashTable));
    if( ht == NULL ) return NULL;

    ht->table = malloc(sizeof(Counter) * TABLE_SIZE);
    if( ht->table == NULL ){
        free(ht);
        return NULL;
    }
    ht->capacity = TABLE_SIZE;
    ht->size = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht->table[i].word = NULL;
        ht->table[i].count = 0;
        ht->table[i].isOccupied = false;
    }
    return ht;
}

/**
 * Uses linear probing to avoid collision
 */
int probe(HashTable *ht, const char *word)
{
    int idx = hash(word);

    while (ht->table[idx].isOccupied && strcmp(ht->table[idx].word, word) != 0)
    {
        idx = (idx + 1) % ht->capacity;
    }
    return idx;
}

/**
 * Stores words and their frequency in the hash table
 */

void ht_store_word(HashTable *ht, const char *word)
{
    int index = probe(ht, word);
    if (ht->table[index].isOccupied)
    {
        if (strcmp(ht->table[index].word, word) == 0)
        {
            ht->table[index].count++;
        }
    }
    else
    {
        ht->table[index].word = strdup(word);
        ht->table[index].count = 1;
        ht->table[index].isOccupied = true;
        ht->size++;
    }
}

/**
 * frees memory allocated for hash table
 */
void free_hash_table(HashTable *ht) {
    if (ht != NULL) {
        for (int i = 0; i < ht->capacity; i++) {
            if (ht->table[i].isOccupied) {
                free(ht->table[i].word);
            }
        }
        free(ht->table);
        free(ht);
    }
}

