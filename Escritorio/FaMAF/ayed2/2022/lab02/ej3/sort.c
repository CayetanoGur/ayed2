#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = izq;
    unsigned int i = izq + 1;
    unsigned int j = der;

    while(i <= j){
        while(goes_before(a[i], a[pivot]) && i < der){
            ++i;
        }
        while(goes_before(a[pivot], a[j]) && j > izq){
            --j;
        }
        if(i <= j){
            swap(a, i, j);
            ++i;
            --j;
        }
    }
    swap(a, i-1, pivot);
    pivot = i -1;
    return pivot;
}


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {

    if(izq < der){
        unsigned int pivot = partition(a, izq, der);
        if(pivot > izq){
            quick_sort_rec(a, izq, pivot - 1);
        }
        if(der > pivot){
            quick_sort_rec(a, pivot + 1, der);
        }
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
