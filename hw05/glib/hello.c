/*
*	GLib Hello World App
*	Kai Austin
*	March 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct {
	char *name;	//String of the word
	int freq;	//Frequency of the word
} Word;

void free_data (gpointer data)
{
	//To free data in the hash table when key/value removed
	free (data);
}

char * strstrip(char * str){
	//Strips a string of its juciness
	int i, j;
    for( i=0; str[i]!=0; ++i )
    {
        while(str[i]=='!' || str[i] == '.' || str[i] == ',' || str[i] == '?' || str[i] == '\'') 
        {
        	/* copy all chars, including NULL at end, over char to left */
        	//There are so many better ways this can be done, however this
        	// is currently the one that works best and it is also the cleanest
	            j=i;
            while(str[j]!=0)
	            {
	                str[j]=str[j+1];
	                ++j;
	            }
	        }
	    }   
}

void addNewWord(GHashTable *hash, char *pch){
	Word *word;
	char * copy;

	//Make new space for the new entry
	word = malloc(sizeof(Word));
	copy = malloc(sizeof(char) * (strlen(pch) + 1) );
	//Copy over the string
	strcpy(copy,pch);
	//set the value of the word to the copy and put the counter at 1
	word->name = copy;
	word->freq = 1;
	//Add the new word to the hash table
	g_hash_table_insert(hash, copy, word);
}

void parseLine (GHashTable *hash, char line[]){
	char * pch;		//For parsing purposes
	Word *keyval;

	//Parse out the punctuation in the line
	//Will hypthetically also ignore \n
	pch = strtok(line, " !?.*,\'\"\n");

	while (pch != NULL){
	
		//String the char of its punctuation, in case any get past...
		strstrip(pch);

		//Get the word, should return pointer to Word struct
		keyval = g_hash_table_lookup(hash, pch);
		//If word in hash table
		if (keyval != NULL){
			//Up the counter of that word in the table
			keyval->freq += 1;

		} else {

			//Otherwise add new Word to the table with freq of 1
			if(pch != ""){
				addNewWord(hash, pch);
			}
		}
	
		pch = strtok(NULL, " \n");
	}
}

void printList(Word *data){
	//Print out the string
	if (data->name != ""){
		g_print("%s : %d \n", data->name, data->freq);
	}
	//Free the data once printed (as no longer use for)
	free (data);
}

int main(){
	
	//Make Hashtable for easy lookup
	GHashTable *hash = g_hash_table_new (g_str_hash, g_str_equal);
	GList *values;	//For extracting the values of the Hash Table
	FILE *file;
	char line[1000];	//Setting 1000 character max per line
	int i;

	//Opening File, read only
	file = fopen("grimms.txt", "r");

	//Go through file and get each line
	while (fgets(line, 1000, file) != NULL){
		//Parse line and put into hash table
		parseLine(hash, line);
	}

	//Close file
	fclose(file);

	values = g_hash_table_get_values(hash);//Get values out of the hash table
	//Print results of GLib
	g_list_foreach(values, (GFunc) printList, NULL);

	//GLib free memory
	g_list_free(values);
	g_hash_table_unref (hash);

	return 0;
}