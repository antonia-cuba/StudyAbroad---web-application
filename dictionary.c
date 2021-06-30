// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
// initialise positive hash value using unsigned int 
unsigned int hash_value;
// initialise (positive) hash table word count 
unsigned int word_count;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_value = (hash_value << 2) ^ word[i];
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dict 
    FILE *file = fopen(dictionary, "r");
    
    // If file is not opened, return false
    if (file == NULL)
    {
        return false;
    }
    
    char word[LENGTH + 1];
    // Scan dict for strings until the end
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node (word)
        node *n = malloc(sizeof(node));
        
        if (n == NULL)
        {
            return false;
        }
        
        // copy word into node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        
        word_count++;
    }
    
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
