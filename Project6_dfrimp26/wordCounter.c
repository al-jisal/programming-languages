/**
 * File: wordCounter.c -- shows an implementation of a word counter using a hash table and linkedlist
 * 
 * Author: Desmond Frimpong
 * Project: 06
 * Date: April 23, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "my_linkedlist.h"
#include "hashtable.h"
#include <time.h>

typedef struct WordCount {
    char *word;
    int count;
} WordCount;

// comparison function for qsort
int compareWords(const void *a, const void *b)
{
    WordCount *wcOne = *(WordCount **)a;
    WordCount *wcTwo = *(WordCount **)b;
    return wcTwo->count - wcOne->count;
}

// comparison function for qsort
int compare_hash(const void *a, const void *b)
{
    const Counter *wc1 = (Counter *)a;
    const Counter *wc2 = (Counter *)b;
    return wc2->count - wc1->count;
}

// frees memory taken up by the word counter struct
void freeWordCount(void *data)
{
    WordCount *wc = (WordCount *)data;
    if (wc != NULL)
    {
        free(wc->word);
        free(wc);
    }
}

// prints out words and their frequency
void printHashTable(HashTable *ht)
{
    // stores the hash table in a temporary array for sorting
    Counter *temp = malloc(ht->size * sizeof(Counter));
    int j = 0;
    for (int i = 0; i < ht->capacity; i++)
    {
        if (ht->table[i].isOccupied)
        {
            temp[j] = ht->table[i];
            j++;
        }
    }
    qsort(temp, j, sizeof(Counter), compare_hash);

    // print top 20 words
    for (int i = 0; i < 20; i++)
    {
        printf("%-20s\t%d\n", temp[i].word, temp[i].count);
    }
    free(temp);
}

// prints out words and their frequency
void printWordCounter(LinkedList *l)
{

    int size = l->size;
    int i = 0;
    WordCount **output = malloc(sizeof(WordCount *) * 100);

    // copies data into an array since directly sorting the linked list is not ideal
    Node *curr = l->head;

    while (curr != NULL && i < size)
    {
        output[i] = (WordCount *)curr->data;
        i++;
        curr = curr->next;
    }

    // sort in descending order
    qsort(output, size, sizeof(WordCount *), compareWords);

    // print top 20 words
    for (int j = 0; j < 20 && j < size; j++)
    {
        printf("%-20s\t%d\n", output[j]->word, output[j]->count);
    }

    free(output);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s [hashmap|linkedlist] <filename>\n", argv[0]);
        return 1;
    }

    const char *data_structure = argv[1];
    const char *filename = argv[2];

    FILE *ptr = fopen(filename, "r");
    if (ptr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    clock_t start, end;
    double time_used;
    char word[100]; // assumes that the longest size of a word = 100
    int idx = 0;
    int c;

    start = clock();
    if (strcmp(data_structure, "hashmap") == 0)
    {
        HashTable *wordTable = init_hash_table();

        // reads a single char from the file
        while ((c = fgetc(ptr)) != EOF)
        {
            // checks if character is an alphabet and add its lower case form to the word array
            if (isalpha(c))
            {
                word[idx++] = tolower(c);
            }

            // if we meet a character which is not an alphabet and idx > 0, it means we have reached the end of one word
            else if (idx > 0)
            {
                word[idx] = '\0';
                ht_store_word(wordTable, word);
                idx = 0;
            }
        }
        // for the last word in the file
        if (idx > 0)
        {
            word[idx] = '\0';
            ht_store_word(wordTable, word);
        }

        printf("\n***Printing Top 20 words***\n");
        printf("\n");
        printHashTable(wordTable);
        free_hash_table(wordTable);
    }
    else if (strcmp(data_structure, "linkedlist") == 0)
    {
        LinkedList *wordList = ll_create();

        // reads a single char from the file
        while ((c = fgetc(ptr)) != EOF)
        {
            // checks if character is an alphabet and add its lower case form to the word array
            if (isalpha(c))
            {
                word[idx++] = tolower(c);
            }

            // if we meet a character which is not an alphabet and idx > 0, it means we have reached the end of one word
            else if (idx > 0)
            {
                word[idx] = '\0';
                ll_store_word(wordList, word);
                idx = 0;
            }
        }

        // for the last word in the file
        if (idx > 0)
        {
            word[idx] = '\0';
            ll_store_word(wordList, word);
        }

        printf("\n***Printing Top 20 words***\n");
        printf("\n");
        printWordCounter(wordList);
        ll_clear(wordList, freeWordCount);
    }

    end = clock(); 

    time_used = ((double)(end - start)); 
    printf("\nTime used: %.2f seconds\n", time_used);
    fclose(ptr);
    return 0;
}