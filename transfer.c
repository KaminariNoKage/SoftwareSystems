#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *fileR;
	FILE *fileW;
	char ch;

	fileR = fopen("file1.txt", "r");
	fileW = fopen("file2.txt", "w");

	while ((ch = fgetc(fileR)) != EOF){
		printf("%c", ch);
	}


	fclose(fileR);
	fclose(fileW);


	return 0;
}