#include <stdio.h>
#include "string.h"
#include <stdlib.h>

int main(void){
	const char *word1 = "Algebra";
	const char *word2 = "Algoritmos";

	string string1 = string_create(word1);
	string string2 = string_create(word2);

	if(string_less(string1, string2)){
		string_dump(string1, stdout);
		printf(" es menor que ");
		string_dump(string2, stdout);
		printf("\n");
	}
	else if(string_eq(string2, string1)){
		string_dump(string1, stdout);
		printf(" es igual que ");
		string_dump(string2, stdout);
		printf("\n");
	}
	else{
		string_dump(string1, stdout);
		printf(" es mayor que ");
		string_dump(string2, stdout);
		printf("\n");
	}

	string1 = string_destroy(string1);
	string2 = string_destroy(string2);

	return 0;

}