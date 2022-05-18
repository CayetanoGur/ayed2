#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s){
	return (s->size <= s->capacity);
}

stack stack_empty(){
	stack s = malloc(sizeof(struct _s_stack));
	s->elems = malloc(sizeof(stack_elem));
	s->size = 0u;
	s->capacity = 1u;
	assert(invrep(s));
	return s;
}

stack stack_push(stack s, stack_elem e){
	assert(invrep(s));
	if(s->size == s->capacity){
		s->capacity = 2u * s->capacity;
		s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
	}
	s->elems[s->size] = e;
	s->size += 1u;
	assert(invrep(s));
	return s;
}

stack stack_pop(stack s){
	assert(invrep(s) && s->size != 0u);
	s->size -= 1u;
	assert(invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(invrep(s));
	return (s->size);
}

stack_elem stack_top(stack s){
	assert(invrep(s) && s->size != 0u);
	stack_elem elem = s->elems[s->size - 1u];
	assert(invrep(s));
	return elem;
}

bool stack_is_empty(stack s){
	assert(invrep(s));
	return (s->size == 0u);
}

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
	free(s);
	s = NULL;
	return s;
}