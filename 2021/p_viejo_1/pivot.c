#include <stdbool.h>
#include <stdio.h>
#define ARRAY_SIZE 100
#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    // -- Completar --
    int k=piv+1;
    int j=0;
    bool res = true;

    while(j <= piv && k <= length && res){
        if(array[j] <= array[piv] && array[piv]<array[k]){
            j = j + 1;
            k = k + 1;   
        }
        else{
            res = false;
        }

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
    int length = 3;
    int a[ARRAY_SIZE]={1,1,6,5};
    printf("ingrese un piv:");
    int piv = scanf("%d", &piv);

    is_pivot(a,length,piv);

}