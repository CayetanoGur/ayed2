#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"
 
struct _s_stack{
    stack_elem elem;
    struct _s_stack * next;
};

static bool invrep(stack s){    
 return s != NULL;
}

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    //assert(invrep(s));
    stack new_elem = malloc(sizeof(struct _s_stack));
    new_elem->elem = e;
    new_elem->next = s;
    
    return new_elem;
}

stack stack_pop(stack s){
    assert(invrep(s));
    stack erase;
    erase = s;
    s = s->next;
    free(erase);
    erase = NULL;
    return s;
}

unsigned int stack_size(stack s){
    //assert(invrep(s));
    stack iterator = s;
    unsigned int length = 0u;
    while (iterator != NULL){
        iterator = iterator->next;
        ++length;
    }
    return length;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    //asstert(invrep(s));
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    //assert(invrep(s));
    unsigned int len = stack_size(s)-1;
    stack_elem *array = malloc((len) * sizeof(stack_elem));
    stack iter = s;
    for (unsigned int i = len; i > 0; --i){
        array[i] = iter->elem;
        iter = iter->next;
    }     
    return array;
}


stack stack_destroy(stack s){
    assert(invrep(s));
    stack aux_s = s;
    stack trash;
    while (aux_s->next != NULL){
        trash = aux_s;
        aux_s = aux_s->next;
        free(trash);
    }
    free(aux_s);
    aux_s = NULL;
    return s;
}

stack print_stack(stack s){
    stack it = s;
    stack_elem top;
    printf("[");
    while(!stack_is_empty(it)){
        top = stack_top(it);
        it = it->next;
        if (it != NULL)
        {
            printf("%d, ", top);
        }else{
            printf("%d", top);
        }   
    } 
    printf("]");
    return s;
}