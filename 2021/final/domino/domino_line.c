#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    domino elem;
    domino_line next;
};

domino_line line_new(domino first) {
    domino_line newl = calloc(1,sizeof(struct _s_line));
    newl->elem = first;
    newl->next = NULL;
    return newl; 
}

domino_line line_add(domino_line line, domino t) {
    // Agregue por izquierda, recordar que cuando lo imprima, lo tengo que dar vuelta
    domino_line aux = calloc(1,sizeof(struct _s_line));
    aux->elem = t;
    aux->next = line;
    line = aux;
    return line;
}

unsigned int line_length(domino_line line) {
    domino_line aux = line;
    unsigned int tam = 0u;
    while (aux != NULL){
        ++tam;
        aux = aux->next;
    }
    return tam;
}

bool line_n_correct(domino_line line, unsigned int n) {
    assert(line_length(line)-1 >= n);
    domino_line aux = line;
    domino_line aux_b = line;
    unsigned int tam = line_length(line);
    bool res = true;
    if (n == 0)
    {
        if (tam > 1)
        {
            aux = aux->next;
            while (aux->next != NULL)
            {
                aux= aux->next;
                aux_b = aux_b->next;
            }
            res = domino_matches(aux->elem, aux_b->elem);
        }
    }
    else if (n == tam-1 )
    {
        res = domino_matches(aux->next->elem, aux->elem);
    }
    // Caso en el que sea una pieza del medio
    else{
        aux = aux->next;
        for (unsigned int i = 0u; i < tam-n-2; i++)
        {
            aux = aux->next;
            aux_b = aux_b->next;
        }
        res = domino_matches(aux->next->elem, aux->elem) &&
                 domino_matches(aux->elem,aux_b->elem);
    }
    return res;
    
}

int line_total_points(domino_line line) {
    int sumat = 0;
    domino_line aux = line;
    while (aux!=NULL)
    {
        sumat+= domino_up(aux->elem) + domino_down(aux->elem);
        aux=aux->next;
    }
    return sumat;
}

domino * line_to_array(domino_line line) {
    domino_line aux = line;
    unsigned int tam = line_length(line);
    domino *line_arr;
    line_arr = calloc(tam, sizeof(domino));
    for (unsigned int i = tam-1; aux!=NULL; i--)
    {
        line_arr[i] = aux->elem;
        aux = aux->next;
    }
    return line_arr;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    domino_line aux;
    while (line != NULL)
    {
        aux = line;
        line = line->next;
        domino_destroy(aux->elem);
        free(aux);
        aux = NULL;
    }
    return line;
}

