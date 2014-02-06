/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

void printLocal () {
	void *chunk1 = malloc(1);
	void *chunk2 = malloc(32);
	printf("Address of local 2 %p\n", &chunk1);
	printf("Address of local 2 %p\n", &chunk2);
}


int main ()
{
    int local = 5;
    void *p = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);

    printLocal();
    
    return 0;
}
