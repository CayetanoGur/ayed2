#include <stdlib.h>
#include <stdio.h>




int main ()
{

    int a = 3;
    int *b = &a;
	void *b2 = b;
   
    *b = 8;
    a = 8; 
    
    printf("%d\n", a);
	printf("%p\n", b);	
	
    return EXIT_SUCCESS;
}
