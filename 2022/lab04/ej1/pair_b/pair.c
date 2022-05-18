#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

pair_t pair_new(int x, int y){
    pair_t pair = malloc(sizeof(pair_t));
    pair->fst = x;
    pair->snd = y;
    return pair;
}

int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t aux = malloc(sizeof(pair_t));
    aux->fst = p->snd;
    aux->snd = p->fst;
    return aux;
}

pair_t pair_destroy(pair_t p){
    free(p);
    p = NULL;
    return p;
}