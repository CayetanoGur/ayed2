/*
typedef struct s_pair_t pair_t;

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

pair_t pair_new(int x, int y){
    pair_t new_pair = {x,y};
    //pair_t new_pair;
    //new_pair.fst = x; ESTO ES LO MISMO QUE ARRIBA 
    //new_pair.snd = y;
    return new_pair;
}

int pair_first(pair_t p){
    return p.fst;
}

int pair_second(pair_t p){
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    pair_t swap = {p.snd, p.fst};
    return swap;
}

pair_t pair_destroy(pair_t p){
    //como no hay memoria reservada (rango vacio) devuelvo p
    return p;
}