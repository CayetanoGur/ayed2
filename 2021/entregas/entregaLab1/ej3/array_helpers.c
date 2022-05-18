#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* Maximum allowed length of the array */
#define MAX_SIZE 100000
#include "array_helpers.h"

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    //your code here!!!
    
    FILE *file_input;
    file_input = fopen (filepath, "r");
    fscanf(file_input, "%u", &max_size);    
    
    unsigned int i = 0;
    // (self note) el loop va tomando cada elemento del arreglo escaneado y lo asigna al mismo lugar del array creado dentro del codigo
    while (i < max_size) {
        fscanf(file_input, "%d", &array[i]);
        i = i + 1;
    }
    fclose(file_input);

    return (max_size);
}

void array_dump(int a[], unsigned int length) {
    //your code here!!!!!
    assert (length < MAX_SIZE);
    fprintf(stdout, "%u \n", length);
    
    unsigned int i = 0;

    while ( i < length ) {
        if (i == 0) {
            printf( "[ %d, ", a[i]);
        }
        else if (i < length-1) {
            printf("%d, ", a[i]);
        }
        else {
            printf("%d ] \n", a[i]);
    }
    i = i + 1;
}
}