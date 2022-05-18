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

bool goes_before(player_t x, player_t y){
    bool goes_before = x.rank <= y.rank;
    return goes_before;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

static void swap(player_t a[], unsigned int left, unsigned int right){
    player_t temp = a[left];
    a[left] = a[right];
    a[right] = temp;
}

static unsigned int partition(player_t a[], unsigned int left, unsigned int right) {
    unsigned int pivot = left;
    unsigned int i = left + 1;
    unsigned int j = right;

    while(i <= j){
        while(goes_before(a[i], a[pivot]) && i < right){
            ++i;
        }
        while(goes_before(a[pivot], a[j]) && j > left){
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


static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {

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

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


