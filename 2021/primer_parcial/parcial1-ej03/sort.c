/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"


bool goes_before(movie_t s1, movie_t s2) {
    if(s1.runtime <= s2.runtime){
      return true;
    }
    else{
      return false;
    }
}

unsigned int array_sorted_until(movie_t movielist[], unsigned int size) {
    
    unsigned int i = 0u;

    while(i < size && goes_before(movielist[i],movielist[i+1])){
      ++i;
    }

    return i;
}

