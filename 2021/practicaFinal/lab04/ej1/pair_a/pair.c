#include "pair.h"
#include <stdio.h>
#include <stdlib.h>

/*TODO: ver invariates, pre y pos*/
pair_t pair_new(int x, int y){
    pair_t new;
    new.fst = x;
    new.snd = y;
    return new;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t swap;
    swap.fst = p.snd;
    swap.snd = p.fst;
    return swap;
}

pair_t pair_destroy(pair_t p){

    return p;
}