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

void parseLine (GHashTable *hash, char line[]){
	char * pch;		//For parsing purposes
	Word *keyval;

	//Parse out the punctuation in the line
	//Will hypthetically also ignore \n
	pch = strtok(line, " ,.-:;");
	while (pch != NULL){
		//If word in hash table
		if (g_hash_table_contains(hash, pch)){
			//Get the word, should return pointer to Word struct
			keyval = g_hash_table_lookup(hash, pch);
			//Up the counter of that word in the table
			keyval->freq += 1;

		} else {

			//Otherwise add new Word to the table with freq of 1
			Word *word = malloc(sizeof(Word));
			word->name = pch;
			word->freq = 1;
			g_hash_table_insert(hash, pch, word);
		}
	
		pch = strtok(NULL, " ,.-:;");
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