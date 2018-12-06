/**************************************************************************
Henry Lindbo
ECE 209 sec 051 summer 2017
this program provides the functions necesary to use a basic autiocomplete function,
	given a partial word and a dictionary with (or without) context words, the 
	user can use these functions to return a list of possible suggestions for 
	completing the word
Either EOS Linux or Virtual Box is fine for grading
***************************************************************************/

#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int wordsindictionary = 0;//initializes number of words in dictionary to 0
int totalbytesused = 3*sizeof(int);//initializes number of bytes used to 0 + these 3 global ints
int totalcontextwords = 0;//initializes number of contextwords to 0

//struct used to make linked list, it is the same one shown on the assignment document
//this makes a linked list of all the words from a dictionary that is read in,
//each of these items is also the head of another linked list, that holds the possible
//context words for each word
struct wordlist{
	char word[100];
	struct wordlist * next;
	struct wordlist * prior;
};
struct wordlist * head;// = malloc(sizeof(struct wordlist));

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
	FILE* file= fopen(filename,"r");//open file
	totalbytesused+=(sizeof(FILE*));//increment bytes used
	
	if(file == NULL)
		return 1;//if no file or bad name return 1 so we know something went wrong
	char word[100];//temporary string for scannin g in contents of file
	totalbytesused+=(100*sizeof(char));//increment bytes used
	
	while(fscanf(file,"%s",word)>0){
		
		AutoComplete_AddWord(word);//add a word
	}
	
	fclose(file);
	totalbytesused-=(sizeof(FILE*));//decrement bytes used
	
	return 0;
}

// Add a word to the autocomplete dictionary.  If the word is already 
// present, it simply does nothing.
void AutoComplete_AddWord(const char *word)
{	
	struct wordlist * temp = head;//temporary list pointer for looking through data 
	
	while(temp!=NULL){//see if word is laready in dictionary
		if(strcmp(temp->word,word)==0){
			return;
		}
		temp = temp->next;
	}
	free(temp);
	
	struct wordlist * tmp = malloc(sizeof(struct wordlist));//make room for new word in list
	totalbytesused+=(sizeof(struct wordlist));//increment bytes used
	
	tmp->next = head;
	tmp->prior = NULL;
	strcpy(tmp->word, word);
	head = tmp;
	
	wordsindictionary++;
}

// Add context for a word to the autocomplete dictionary.  If the word
// is not already present, then add it. If the word is present, add 
// prior to its context. If prior is already present, do not add it a 
// second time.
void AutoComplete_AddContext(const char *word, const char * prior)//still need to make sure prior isn't added twice!!!
{
	AutoComplete_AddWord(word);
	struct wordlist * tmp = head;//temporary list pointer for looking through data 
	
	while(tmp != NULL){
		if (strcmp(tmp->word,word)==0){
			
				struct wordlist * temp = tmp->prior;//temporary list pointer for looking through data 
	
				while(temp!=NULL){//see if word is laready in dictionary
					if(strcmp(temp->word,prior)==0){
						return;
					}
					temp = temp->next;
				}
				free(temp);
			
			struct wordlist * p = malloc(sizeof(struct wordlist));//makes room for new context word
			totalbytesused+=(sizeof(struct wordlist));//increment bytes used
			
			strcpy(p->word, prior);
			totalcontextwords++;
			p->next = tmp->prior;
			tmp->prior = p;
			break;
		}
		tmp = tmp->next;
	}
}


// Return an integer specifying the total amount of memory
// used by the auto-completer.
// Arguments: None
// Return value: integer that specifies in bytes the amount
//               of memory used, including global/static variables.
int AutoComplete_TotalMemoryUsed()
{
  return totalbytesused;
}

// Return an integer specifying the total number of words
// added to the auto-completer.
int AutoComplete_NumberOfDictionaryWords()
{
  return wordsindictionary;
}

// Return an integer specifying the total number of words
// used for semantic context.
int AutoComplete_NumberOfContextWords()
{
  return totalcontextwords;
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
	int matches = 0;//number of possible completions of partial word
	totalbytesused+=(sizeof(int));//increment bytes used
	
	struct wordlist * tmp = head;//temporary list pointer for looking through data 
	
	
	if(*prior == '\0'){
		while(tmp!=NULL && matches<size_of_array){
			if(strncmp(tmp->word,partial_word,strlen(partial_word))==0){
				completions[matches]=tmp->word;
				matches++;
			}
			tmp = tmp->next;
		}
	}else{
		struct wordlist * p = malloc(sizeof(struct wordlist));//temporary list pointer for looking through data 
		totalbytesused+=(sizeof(struct wordlist));//increment bytes used
		
		while(tmp!=NULL && matches<size_of_array){//look through array for matching word
			if(strncmp(tmp->word,partial_word,strlen(partial_word))==0){
				p = tmp->prior;
				while(p != NULL && matches<size_of_array){//look through context words to find match
					if(strcmp(p->word, prior)==0){
						completions[matches]=tmp->word;
						matches++;
					}
					p = p->next;
					
				}
			}
			tmp = tmp->next;
		}
		free(p);
		totalbytesused-=(sizeof(struct wordlist));//decrement bytes used
	}
	totalbytesused-=(sizeof(int));//decrement bytes used
	return matches;
}









