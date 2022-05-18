#include "pair.h"
#include <stdio.h>
#include <stdlib.h>

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    //creo el par
    pair_t new_pair;
    //pido memoria
    new_pair = malloc(sizeof(struct s_pair_t));
    //seteo los campos
    new_pair->fst = x;
    new_pair->snd = y;
    //return
    return new_pair;
}

int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t swap = pair_new(p->snd,p->fst);
    return swap;
}

pair_t pair_destroy(pair_t p){
    free(p); //liverar la memoria de un puntero y hay que apuntarlo a null
    p = NULL;
    return p;
}