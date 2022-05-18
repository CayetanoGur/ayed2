#include <stdio.h>
#include <stdlib.h>
int main(void) {
	int size = 10;
    int *p = NULL;
    p = malloc(sizeof(int));
    *p = size;
    
    



    printf("size = %u\n", size);
    printf("p = %d\n", *p);
   	printf("\n\n");
}

