#include <stdlib.h>
#include <stdio.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size,const char *filepath) {
    FILE *file = NULL;
    file = fopen(filepath, "r");
    //Tengo que considerar si el file esta bien leido o no.
    if (file == NULL){
        fprintf(stderr, "Error.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, "%u", &size);
    //Tengo que ver que el tamaño del arreglo sea menor que el tamaño permitido y tiene que ser distinto de 1 ya que toma un int del tamaño y despues un array.
    if(res != 1 || size > max_size){
        fprintf(stderr, "Error.\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < size; ++i){
        res = fscanf(file, "%d", &array[i]);
    }
    fclose(file);
    return(size);
}
    

void array_dump(int a[], unsigned int length) {
    fprintf(stdout, "%u\n", length);
    for (unsigned int i = 0u; i < length; ++i) {
        fprintf(stdout, "%i", a[i]);
        if (i < length - 1) {
            fprintf(stdout, " ");
        } else {
            fprintf(stdout, "\n");
        }
    }
}