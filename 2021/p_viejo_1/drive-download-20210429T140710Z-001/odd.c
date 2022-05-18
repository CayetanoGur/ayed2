#include <stdbool.h>
#include <stdio.h>
#define ARRAY_SIZE 100
#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
    // -- Completar --
    unsigned int i = 0;
    bool res = true;
    while(i < length && res){
        if ((i%2)==1 && (i+2)<length){
            res = array[i]<array[i+2];
        }
    i = i + 1;
    }
    if(res == 1){
        printf("True\n");
    }
    else{
        printf("False\n");

    }
    return res;
}

int main(){
    int length = 5;
    int array[ARRAY_SIZE] = {5,1,8,2,3}; 
    /*para hacerlo mas rapido directamente defini el arreglo aca, asi no perdia tiempo del parcial pidiendo el arreglo 
    y el largo por teclado, para probar los distintos ejemplos de array tendriamos que cambiar el array y el length*/

    is_odd_sorted(array,length);

    return 0;
}

