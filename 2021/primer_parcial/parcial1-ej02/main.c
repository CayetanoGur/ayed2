#include <stdbool.h>
#include "even.h"
//Incluyo stdio para usar prints con el motivo de ir siguiendo el codigo por pantalla
#include <stdio.h>
//Incluyo el stdlib por el exit failure 
#include <stdlib.h>
#define ARRAY_SIZE 100



int main(){
    int length = 5;
    int array[ARRAY_SIZE] = {1,6,2,0,-1}; 
    
    is_even_sorted(array,length);
}