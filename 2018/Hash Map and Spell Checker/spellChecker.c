/*
* CS 261 Data Structures
* Assignment 5
* Name: Forrest Allen
* Date: 6/4/2018
* Description: spellchecker.c takes user input and checks to see if the word is there. if it is 
* the person is told that it is correct. If not, they are given what could be the word.
*/
#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
	char * word = nextWord(file);
	while (word) {
		hashMapPut(map, word, 1);
		free(word);
		word = nextWord(file);
	}

	free(word);

}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
	clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("\nEnter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
		else if (hashMapContainsKey(map, inputBuffer))
		{
			printf("The inputted word %s is spelled correctly\n", inputBuffer);
		}
		else
		{
			int index = HASH_FUNCTION(inputBuffer) % hashMapCapacity(map);
			HashLink* temp = map->table[index];
			printf("The inputted word %s is not spelled correctly\n", inputBuffer);
			printf("Did you mean: ");
			int vals=0;
			while(vals<5)
			{
				if (temp->key[0] == inputBuffer[0])
				{
					printf("%s ", temp->key);
					temp = temp->next;
					vals++;
				}
				else
				{
					temp = temp->next;
				}
			}
		}
    }
    
    hashMapDelete(map);
    return 0;
}
