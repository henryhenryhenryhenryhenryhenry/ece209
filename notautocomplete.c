#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int qsize = 200;

struct word{
	char actualword[100];
};
typedef struct word Item;
typedef int Key;
struct HashNode{
	Key key;
	Item data;
	struct HashNode * next;
};
typedef struct HashNode hashnode;

hashnode **hashtablearray = NULL;
int htsize = 0;

//-------------------------------------------------------------------

void htinitialize(int size){
	hashtablearray = malloc(size*sizeof(hashnode*));
	int i;
	for(i=0;i<size;i++)
		hashtablearray[i]=NULL;
	htsize = size;
}

//was going to use Dan Bernstein's hash but didn't
int DBhash(char *v){
	int retval;
	retval = (int)v[0];
	return retval;
	
	/*
	unsigned long hash = 5381;
	int c;
	while((c=*v++))
		hash = ((hash << 5) + hash) ^ c;
	return hash%htsize;
	*/
}

void htinsert(Key key, Item data){
	int index = key;
	
	hashnode *tmp = malloc(sizeof(hashnode));
	tmp->key = key;
	tmp->data = data;
	
	tmp->next = hashtablearray[index];
	
	hashtablearray[index] = tmp;
}

int htfind(char* k, Item * data){
	int index = DBhash(k);
	
	hashnode * head = hashtablearray[index];
	
	int comparisons = 0;
	
	while(head){
		comparisons++;
		if((head->data).actualword == k){
			*data = head->data;
			return 1;
		}
		head = head->next;
	}
	return 0;
}

// Add the words in file specified by filename to the
// auto-complete engine. This may be called multiple
// times with different filenames.  The words in the new
// file are appended to the existing list.  Duplicates are not 
// allowed.
// Argument: filename - file with words that need to be added
//                      to the table
// Return value: 0: success
//               1: bad file name
int AutoComplete_LoadDictionary(const char *filename)
{
	
	
	return 1;
}

// Add a word to the autocomplete dictionary.  If the word is already 
// present, it simply does nothing.
void AutoComplete_AddWord(const char *word)
{
	static int wordsadded = 0;
	if(wordsadded <= 0){
		htinitialize(qsize);
	}
	
	Item* data = malloc(sizeof(Item));
	strcpy(data->actualword, word);//data->actualword = word;
	

	htinsert(DBhash(data->actualword),*data);
	
	wordsadded++;
}


// Add context for a word to the autocomplete dictionary.  If the word
// is not already present, then add it. If the word is present, add 
// prior to its context. If prior is already present, do not add it a 
// second time.
void AutoComplete_AddContext(const char *word, const char * prior)
{
  
}


// Return an integer specifying the total amount of memory
// used by the auto-completer.
// Arguments: None
// Return value: integer that specifies in bytes the amount
//               of memory used, including global/static variables.
int AutoComplete_TotalMemoryUsed()
{
  return 0;
}

// Return an integer specifying the total number of words
// added to the auto-completer.
int AutoComplete_NumberOfDictionaryWords()
{
  return 0;
}

// Return an integer specifying the total number of words
// used for semantic context.
int AutoComplete_NumberOfContextWords()
{
  return 0;
}

// For a given partial word, return no more than size possible
// completions.
// Arguments: prompt - the beginning of a word to complete
//            prior -  a string with the word that came before it; it 
//                     may be NULL, and if so, no context is needed 
//                     for a match. Otherwise, the prior must be part 
//                     of the context of all returned words.
//            completions - an array to store the completions inside
//            size_of_array - size of the completions array
//
// Return value: number of completions returned in the array; 0 means
//               nothing was returned
//
int AutoComplete_Suggestion(const char *partial_word, const char *prior, const char *completions[], int size_of_array)
{
	int matches = 0;
	int index = DBhash(partial_word[0]);
	
	Item * tmp = index;
	
	return matches;
}















