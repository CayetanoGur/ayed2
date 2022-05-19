#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};


static bool invrep(stack s){    
 return s != NULL;
}

stack stack_empty(){
    stack s;
    s->elems = 0u;
    s->capacity = 0u;
    s->elems = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    /*
    Yo deberia pedir memoria para un elemento mas cada vez que hago un push
    */
    unsigned int size = s->size + 1;
    s->size = size;
    
    for (unsigned int i = size; i > 0; --i){
        s->elems[i] = s->elems[i-1];
    }
    s->elems[0] = e;
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    for (unsigned int i = 0; i < s->size; ++i){
        s->elems[i] = s->elems[i+1];
    }
    s->size = s->size-1;
   
    return s;
}

/* falta hacer el size de orden constante */

unsigned int stack_size(stack s){
    //assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    return s->elems[0];
}

bool stack_is_empty(stack s){
    //asstert(invrep(s));
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    //assert(invrep(s));
    unsigned int len = stack_size(s);
    stack_elem *array = calloc(len, sizeof(stack_elem));
    
    return array;
}


stack stack_destroy(stack s){
    assert(invrep(s));
   
    return ;
}

// stack print_stack(stack s){
//     stack it = s;
//     stack_elem top;
//     printf("[");
//     while(!stack_is_empty(it)){
//         top = stack_top(it);
//         it = it->next;
//         if (it != NULL)
//         {
//             printf("%d, ", top);
//         }else{
//             printf("%d", top);
//         }   
//     } 
//     printf("]");
//     return s;
// }