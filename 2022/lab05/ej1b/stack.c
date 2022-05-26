#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    size_t size;
    struct _s_stack * next;
};

static bool invrep(stack s){
    bool res = s != NULL;
    return res;
}

stack stack_empty() {
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));
    s->size = 0;
    s->next = NULL;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    stack new_elem = NULL;
    new_elem = malloc(sizeof(struct _s_stack));
    new_elem->elem = e;
    new_elem->size = s->size + 1u; 
    new_elem->next = s;
    assert(invrep(s));
    return new_elem;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    stack s_aux = s;
    size_t tmp = s->size;
    s = s->next;
    free(s_aux);
    s_aux = NULL;
    s->size = tmp - 1u;
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) { 
    unsigned int len = stack_size(s);
    stack_elem *array = calloc(len, sizeof(stack_elem));
    stack iter = s;
    for (unsigned int i = len; i > 0; --i){
        array[i-1] = iter->elem;
        iter = iter->next;
    }     
    return array;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    stack s_aux = NULL;
    while (s != NULL) {
        s_aux = s;
        s = s->next;
        free(s_aux);
    }

    return s;
}
