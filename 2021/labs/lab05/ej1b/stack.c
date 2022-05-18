#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    stack next;
    unsigned int size;
};

/* bool invrep(stack s){
    bool empty = false;
    bool not_empty = false;

    if (s != NULL){
        empty = s->size == 0 && s->elem == NULL;
        not_empty = s->size != 0 && s->elem != NULL;
    }

    return empty || not_empty;
}
*/

stack stack_empty(){
    stack s = NULL;
    s->next = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    
    stack new_node = malloc(sizeof(struct _s_stack));
    new_node->elem = e;
    new_node->next = s;
    if (s == NULL){
        new_node->size = 1u;
    }
    else{
        new_node->size = s->size + 1u;
    }
    s = new_node;
    free(new_node);
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
    if (s == NULL){
        res = 0u;
    }
    else{
        res = s->size;
    }
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
    stack p = s;
    unsigned int length = s->size;

    if (s != NULL){
        a = calloc(length, sizeof(stack_elem));
        
         for(unsigned int i = 0u; i < length; ++i){
            a[length-i-1u] = p->elem;
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