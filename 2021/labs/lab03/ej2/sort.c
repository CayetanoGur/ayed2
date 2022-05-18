/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

void swap(player_t a[], unsigned int i, unsigned int j){
    player_t temp;
    if(i != j){
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

bool goes_before(player_t x, player_t y){
    // completar aquí
    if(x.rank <= y.rank){
        return true;
    }
    else{
        return false;
    }
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}
//partition of quicksort
static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
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
//quicksort

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
   unsigned int piv = partition(a,izq,der);
   if (piv > izq){
        quick_sort_rec(a,izq,piv-1);
   } 
   if (piv < der){
       quick_sort_rec(a,piv+1,der);
   }
}

void sort(player_t a[], unsigned int length) {
    // completar aquí
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

