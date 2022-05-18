
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

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

boolean array_is_sorted(int a[], unsigned int max_size){
    boolean res = true;
    for (unsigned int i = 0; i < max_size - 1 && res == true; ++i){
        if (a[i] <= a[i+1]){
            res = true;
        }
        else{
            res = false;
        }
    }
    if (res == true){
        printf("El arreglo esta ordenado\n");
    }
    else{
        printf("El arreglo esta desordenado\n");
    }
    return (res);
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);

    array_is_sorted(array, length);
    
    return (EXIT_SUCCESS);
}
