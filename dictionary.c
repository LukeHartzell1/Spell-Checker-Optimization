// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;
unsigned int word_count = 0;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int  hash_index = hash(word);
    node *current = table[hash_index];
    while (current != NULL)
    {
        if (strcasecmp(word, current->word) == 0)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 1;
    int total = 0;
    // TODO: Improve this hash function
    while (word [i] != '\0')
    {
        total += toupper(word[i]) - 'A'; //gets the sum of all characters besides the first one
        i++;
    }
    return (total * toupper(word[0])) % N; //multiplies value of first character by the sum of the rest of the charactres
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    unsigned int index;
    FILE *ptr = fopen(dictionary, "r"); //open the dictionary file
    if (ptr == NULL)
    {
        printf("File doesn't exist.\n");
        return false;
    }
    int length;
    char buffer[LENGTH + 1];
    while (fscanf(ptr, "%s", buffer) != EOF)
    {
        index = hash(buffer);
        node *temp = malloc(sizeof(node)); //create new node to store the word
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, buffer);  //copy word into the buffer
        temp->next = table[index];   //sets the value of the temp node to be whatever is at the index
        table[index] = temp; //prepends temp node
        word_count++;
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current = table[0];
    node *deletion = table[0];
    for (int i = 0; i < N; i++)
    {
        current = table[i];
        while (current != NULL)
        {
            deletion = current;
            current = current->next; //current goes to the next node while deletion stays on the past one
            free(deletion);
        }
        if (i == N - 1 && current == NULL)
        {
            return true;
        }
    }
    return false;
}
