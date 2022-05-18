#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
   unsigned int piv;
   unsigned int i;
   unsigned int j;
   piv = izq;
   i = izq + 1;
   j = der;
   
   while ( i <= j){
       if (goes_before(a[i],a[piv])){
           i = i + 1;

       }else if (goes_before(a[j], a[piv])){
           swap(a,i,j);
           i = i + 1;
           j = j - 1;

       }else if (goes_before(a[piv],a[j])){
           j = j - 1;
       }
    }

    swap(a,izq,j);
    piv = j;

  return (piv); 
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
   unsigned int piv = partition(a,izq,der);
   if (piv > izq){
        quick_sort_rec(a,izq,piv-1);
   } 
   if (piv < der){
       quick_sort_rec(a,piv+1,der);
   }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

