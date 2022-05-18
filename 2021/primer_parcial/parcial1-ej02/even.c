/*En el ejercico 1 me falto cambiar el return y verificar que el largo sea mayor a 1, lo comento porque subi mal el ejercicio anterior 
y no se puede cambiar*/

#include <stdbool.h>
#include "even.h"
//Incluyo stdio para usar prints con el motivo de ir siguiendo el codigo por pantalla
#include <stdio.h>
//Incluyo el stdlib por el exit failure 
#include <stdlib.h>


bool is_even_sorted(int array[], unsigned int length) {
    
    if (length < 1){
        fprintf(stderr, "Array length invalid");
        exit(EXIT_FAILURE);
    }
    
    unsigned int i = 0u;
    bool res = true;

    while(i < length && res){

        if((i%2)==0 && (i+2)<=length){
            res = array[i]<array[i+2];
        }
        ++i;
    }

    //Pongo este if para mostrar por pantalla los valores del resultado

    if(res == 1){
        printf("TRUE. The array is sorted in all of its even positions\n");
    }
    else{
        printf("FALSE. The array isn´t sorted in all af its even positions\n");

    }

    return res;
}
