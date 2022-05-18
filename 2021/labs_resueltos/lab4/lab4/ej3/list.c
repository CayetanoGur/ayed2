#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include <assert.h>

struct _node {
	list_elem elem;
	struct _node * next;
};


list empty(void){
	list l = NULL;
	return l;
}

list addl(list l, list_elem e){
	list p;
	p = malloc(sizeof(struct _node));
	p->elem = e;
	p->next = l;
	l = p;
	return l;
}

bool is_empty(list l){
	return (l == NULL);
}

list_elem head(list l){
	assert(!is_empty(l));
	return l->elem;
}

list tail(list l){
	assert(!is_empty(l));
	list p;
	p = l;
	l = l->next;
	free(p);
	p = NULL;
	return l;
}

list addr(list l, list_elem e){
	list p, q;
	q = malloc(sizeof(struct _node));
	q->elem = e;
	q->next = NULL;
	if(!is_empty(l)){
		p = l;
		while(!is_empty(p->next)){
			p = p->next;
		}
		p->next = q;
	}
	else{
		l = q;
	}
	return l;
}

unsigned int length(list l){
	list p;
	unsigned int n;
	n = 0u;
	p = l;
	while(!is_empty(p)){
		n++;
		p = p->next;
	}
	return n;
}

list concat(list l, list l0){
	list p;
	p = l;
	while(!is_empty(p->next)){
		p = p->next;
	}
	p->next = l0;
	return l;
}

list_elem index(list l, unsigned int n){
	assert(length(l) > n);
	list_elem e;
	list p;
	p = l;
	for(unsigned int i = 0u; i < n; ++i){
		p = p->next;
	}
	e = p->elem;
	return e;
}

list take(list l, unsigned int n){
	list p, q;
	unsigned int i;
	p = l;
	i = 0u;
	while(i < n && i < length(l)){
		p = p->next;
		++i;
	}
	while(!is_empty(p)){
		q = q;
		p = p->next;
		free(q);
	}
	return l;
}

list drop(list l, unsigned int n){
	list p;
	unsigned int i;
	i = 0u;
	while(i < n && !is_empty(l)){
		p = l;
		l = l->next;
		free(p);
		++i;
	}
	return l;
}

list copy_list(list l){
	list p, q, list2;
	if(is_empty(l)){
		list2 = empty();
	}
	else{
		q = malloc(sizeof(struct _node));
		p = l;
		list2 = q;
		while(!is_empty(p->next)){
			q->next = malloc(sizeof(struct _node));
			q->elem = p->elem;
			p = p->next;
			q = q->next;
		}
		q->elem = p->elem;
		q->next = NULL;
	}
	return list2;
}

/* Destroy */
list list_destroy(list l){
	list p;
	while(!is_empty(l)){
		p = l;
		l = p->next;
		free(p);
	}
	return l;
}