// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

unsigned int hashvalue;
unsigned int wordnumber;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Apply the hash function to get the index for the table
    int index = hash(word);

    // Access the table at the correct index
    node *hashtable = table[index];

    // Go over the hashtable and compare the words
    while (hashtable != NULL)
    {
        if (strcasecmp(hashtable->word, word) == 0)
        {
            return true;
        }

        hashtable = hashtable->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Get the index number for the first 2 letters, getting a shorter list in each "bucket"
    int index0 = (toupper(word[0])) - 65;
    int index1 = (toupper(word[0])) - 65;
    return index0 + index1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary in read mode, return false fi error while opening
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    // Reading the input and copying it into header
    char word[LENGTH + 1];
    while (fscanf(input, "%s", word) != EOF)
    {
        // Allocate memory for temp node, free memory and close file if error
        node *nword = malloc(sizeof(node));
        if (nword == NULL)
        {
            free(nword);
            fclose(input);
            return false;
        }
        // Copying into temp node the word
        strcpy(nword->word, word);

        // Getting the index for the table
        hashvalue = hash(word);

        nword -> next = table[hashvalue];
        table[hashvalue] = nword;

        // Keep tracking of the number of words
        wordnumber++;
    }
    fclose(input);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Just calling the variable tracked in load
    return wordnumber;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate each of the "buckets", and freeing each memory previously allocated
    for (int i = 0; i < N; i++)
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    return true;
}
