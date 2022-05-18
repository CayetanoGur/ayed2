#include "pair.h"
#include <stdlib.h>

struct s_pair_t{
    int fst;
    int snd;
};


pair_t pair_new(elem x, elem y){
    pair_t new;
    new = malloc(sizeof(struct s_pair_t));
    new->fst = x;
    new->snd = y;

    return new;
}

int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t swap = malloc(sizeof(struct s_pair_t));
    swap->fst = p->snd;
    swap->snd = p->fst;

    return swap;
}

pair_t pair_destroy(pair_t p){
    free(p);
    p = NULL;
    return p;
}