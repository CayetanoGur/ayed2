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
    stack s = malloc(sizeof(struct _s_stack));
    s->size = 0u;
    s->capacity = 1u;
    s->elems = malloc(sizeof(stack_elem));
    return s;
}

stack stack_push(stack s, stack_elem e){
    /*
    Yo deberia pedir memoria para un elemento mas cada vez que hago un push
    */
    if (s->size == s->capacity){
        s->capacity = 2u * s->capacity;
        s->elems = realloc(s->elems,s->capacity * sizeof(stack_elem));
    }
    s->elems[s->size] = e;
	s->size += 1u;
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    --s->size;
    return s;
}

/* falta hacer el size de orden constante */

unsigned int stack_size(stack s){
    //assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s){
    //asstert(invrep(s));
    return s == NULL;
}

// stack_elem *stack_to_array(stack s){
//     //assert(invrep(s));
//     unsigned int len = stack_size(s);
//     stack_elem *array = malloc(len-1 * sizeof(stack_elem));
//     for (unsigned i = 0; i < len; ++i){
//         array[i] = s->elems[i];
//     }
//     return array;
// }

stack_elem *stack_to_array(stack s){
	assert(invrep(s));
	stack_elem *array;
	if(stack_is_empty(s)){
		array = NULL;
	}
	else{
		array = calloc(stack_size(s), sizeof(stack_elem));
		for(unsigned int i = 0u; i < stack_size(s); ++i){
			array[i] = s->elems[i];
		}
	}
	assert(invrep(s));
	return array;
}


stack stack_destroy(stack s){
    assert(invrep(s));
    free(s->elems);
    s->elems = NULL;
    free(s);
    s = NULL;
    return s;
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