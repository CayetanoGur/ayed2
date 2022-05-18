/*
typedef struct s_pair_t * pair_t;

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y);
int pair_first(pair_t p);
int pair_second(pair_t p);
pair_t pair_swapped(pair_t p);
pair_t pair_destroy(pair_t p);

*/

#include "pair.h"
#include <stdlib.h>

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
    return pair_new(p->snd,p->fst);;
}

pair_t pair_destroy(pair_t p){
    free(p); //liverar la memoria de un puntero y hay que apuntarlo a null
    p = NULL;
    return p;
}