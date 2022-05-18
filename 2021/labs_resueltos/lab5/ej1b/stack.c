#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _node *node;

struct _node{
	struct _node *next;
	stack_elem elem;
};

struct _s_stack{
	unsigned int size;
	struct _node *point;
};

bool invrep(stack s){
	bool b;
	b = (s != NULL);
	if(s->size == 0u){
		b = b & (s->point == NULL);
	}
	else{
		b = b & (s->point != NULL);
	}
	return b;
}
 
stack stack_empty(void){
	stack s = malloc(sizeof(struct _s_stack));
	s->point = NULL;
	s->size = 0u;
	assert(invrep(s));
	return s;
}

stack stack_push(stack s, stack_elem e){
	assert(invrep(s));
	node p = malloc(sizeof(struct _node));
	p->elem = e;
	p->next = s->point;
	s->point = p;
	s->size += 1u;
	p = NULL;
	assert(invrep(s));
	return s;
}

stack stack_pop(stack s){
	assert(s->point != NULL && s->size > 0u && invrep(s));
	node p;
	p = s->point;
	s->point = s->point->next;
	s->size = s->size - 1u;
	free(p);
	p = NULL;
	assert(invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(invrep(s));
	return (s->size);
}

stack_elem stack_top(stack s){
	assert(s->point != NULL && s->size > 0u && invrep(s));
	return (s->point->elem);
}

bool stack_is_empty(stack s){
	assert(invrep(s));
	return (s == NULL && s->size == 0u);
}

stack_elem *stack_to_array(stack s){
	assert(invrep(s));
	node p;
	stack_elem *array;
	if(stack_is_empty(s)){
		array = NULL;
	}
	else{
		array = calloc(stack_size(s), sizeof(stack_elem));
		p = s->point;
		for(unsigned int i = stack_size(s); i > 0u; --i){
			array[i-1u] = p->elem;
			p = p->next;
		}
	}
	p = NULL;
	assert(invrep(s));
	return array;
}

stack stack_destroy(stack s){
	assert(invrep(s));
	node p;
	while(s->point != NULL){
		p = s->point;
		s->point = s->point->next;
		free(p);
	}
	free(s);
	p = NULL;
	s = NULL;
	return s;
}

