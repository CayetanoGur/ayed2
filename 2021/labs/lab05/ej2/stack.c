#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool inverp(stack s){
    bool res;
    if (s != NULL){
        res = (s->size <= s->capacity);
    }

    return res;
}

stack stack_empty(){
    return NULL;
}


stack stack_push(stack s, stack_elem e){
    if (s == NULL){
        s = malloc(sizeof(struct _s_stack));
        s->capacity = 1u;
        s->size = 1u;
        s->elems = calloc(s->capacity,sizeof(stack_elem));
        s->elems[0] = e;
        
    }
    else{ 
        if(s->size >= s->capacity){
            s->capacity = s->capacity*2;
            s->elems[s->size] = e;
            s->size = s->size + 1;
        }
        else {
            s->elems[s->size] = e;
            s->size = s->size + 1;
        }
    }
    //assert(inverp(s));
    return s;
}


stack stack_pop(stack s){
    assert(inverp(s));
    stack new = stack_empty();
    unsigned int length = stack_size(s)-1;

    for (unsigned int i = 0; i < length; ++i){
        new = stack_push(new, s->elems[i]);
    }

    s = stack_destroy(s);
    assert(inverp(new));
    return new;
}


unsigned int stack_size(stack s){
    assert(inverp(s));
    return s->size;
}


stack_elem stack_top(stack s){
    assert(inverp(s));
    return s->elems[s->size-1];
}


bool stack_is_empty(stack s){
    return s == NULL;
}


stack_elem *stack_to_array(stack s){
    unsigned int length = s->size;
    stack_elem *a = calloc(length, sizeof(stack_elem));

    for (unsigned int i = length; i > 0; --i){
        a[i] = stack_top(s);
        s = stack_pop(s);
    }

    return a;
}

stack stack_destroy(stack s){
    assert(inverp(s));
    if(s != NULL){
        free(s->elems);
        free(s);
        s = NULL;
    }

    return s;
}
