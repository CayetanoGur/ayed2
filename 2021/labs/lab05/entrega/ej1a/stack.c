#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    stack next;
};



stack stack_empty(){
    stack s = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    
    stack new_node = malloc(sizeof(struct _s_stack));
    new_node->elem = e;
    new_node->next = s;
    s = new_node;
    new_node = NULL;
    
    return s;
}

stack stack_pop(stack s){
    assert(s != NULL);
    //stack aux_stack;
    //aux_stack = s;
    s = s->next;
    //free(aux_stack);
    //aux_stack = NULL;
    
    return s;
}

unsigned int stack_size(stack s){
    unsigned int res = 0u;
    stack aux = s;

    while(aux != NULL){
        aux = aux->next;
        res = res + 1;
    }
    free(aux);
    aux = NULL;
    return res;
}

stack_elem stack_top(stack s){
    assert(!(stack_is_empty(s)));
    return s->elem;
}

bool stack_is_empty(stack s){
    return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem *a = NULL;

    if (s != NULL){
        unsigned int size = stack_size(s);
        a = calloc(size, sizeof(stack_elem));
        stack p = s;
        for(unsigned int i = 0u; i < size; ++i){
            a[size-i-1u] = p->elem;
            p = p->next;
        }
    }
    return a;
}

stack stack_destroy(stack s){
    stack p = NULL;
    
    while (s != NULL){
        p = s;
        s = s->next;
        free(p);
        p = NULL;
    }
    return s;
}