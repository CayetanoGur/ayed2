#include <stdlib.h>
#include <stdio.h>




int main ()
{
	int var=0;
	int *p = NULL; //puntero que apunta a algo de tipo int (guarda un direccion de meoria)
	var = 7;
	p = &var; // puedo guardar la direccion de memoria de una variable en un puntero
			  // p apunta a la direccion de memoria de var
			  // cuando tengo un puntero que apunta a una var se llama aliasing
	*p = 3;
	printf("%d\n", var);
	printf("%p\n", &var);
	printf("%p\n", &p);
    return EXIT_SUCCESS;
}
