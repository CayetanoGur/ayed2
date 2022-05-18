#include "sorted.h"
//Incluyo el stdio para usar printf
#include <stdio.h>
//voy a declarar un tamaño de arreglo para probar ejemplos, estos ejemplos los use en un main que cree para testear.
#define ARRAY_SIZE 100

unsigned int sorted_until(int array[], unsigned int size) {
    unsigned int i=0;
    /*hago un while que avance desde el primer elemento del arreglo hasta el tamaño del mismo, y se corta el while
    cuando un elemento es mayor al siguiente*/
    while(i < size && array[i] <= array[i+1]){
        ++i;
    }
    printf("The array is sorted from the position 0 to %d\n", i);

    return i;
}
