#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct _node{
    list_elem elem;
    struct _node * next;
};


//CONSTRUCTORS

/*Creates empty list*/
list empty(){
    /*
    Lo que esta haciendo es esto:
    list empty = NULL;
    return empty;
    */
    return NULL;
}

/*adds an element at the left of the list*/
list addl(list_elem e, list l){
    list new_elem = malloc(sizeof(struct _node));
    new_elem->elem = e;
    new_elem->next = l;
    //puedo hacer el returno de new_elem directamente o copiar l con new_elem y devolver l
    l = new_elem;
    return l;
}

//OPERATIONS

/*Returns True if the list is empty*/
bool is_empty(list l){
    return l == NULL;
}

/*Return the first element of the list*/
list_elem head(list l){
    assert(l != NULL);
    return l->elem;
}

/*Erase the first element of the list*/
list tail(list l){
    // l = l->next;
    // return l;
    //aca haymemory leak, me quedo un nodo colgando
    list auxiliar_node = malloc(sizeof(struct _node));
    auxiliar_node = l;
    l = l->next;
    free(auxiliar_node);
    auxiliar_node = NULL;
    return l;
}

/*Adds an element to the right of the list*/
list addr(list l, list_elem e){
    //list iterator_list = malloc(sizeof(struct _node));
    list new_node = malloc(sizeof(struct _node));
    list iterator_list = l;
    new_node->elem = e;
    new_node->next = NULL;
    while(iterator_list->next != NULL){
        iterator_list = iterator_list->next;
    }
    iterator_list->next = new_node;
    return l;
}

/*Returns the lenght of the list as an unsigned int type*/
unsigned int length (list l){
    /*
    list iterator_list = malloc(sizeof(struct _node));
    Porque no hace falta hacer esto y puedo directamente copiar la lista sin reservar memoria?
        porque estoy apuntando con dos punteros a la misma direccion de memoria y ambos modifican lo mismo. ¿¿??
    */
    unsigned int length = 0u;
    list iterator_list = l;
    if(l != NULL){
        while(iterator_list->next != NULL){
        iterator_list = iterator_list->next;
        ++length;
        }
    }
    // free(iterator_list);
    // iterator_list = NULL; --> no hace falta que le haga un free porque no aloque memoria.
    return length;
}

/*Returns the concatenation of two lists*/
list concat(list l0, list l1){
    list it_list = l0;
    while (it_list->next != NULL){
        it_list = it_list->next;
    }
    it_list->next = l1;
    return l0;    
}

/*Returns the index n of a list.
PRE: length(l)>n*/
list_elem index(list l, unsigned int n){
    assert(length(l) > n);
    list_elem ret;
    list it_list = l;
    for (unsigned int i = 0; i < n; ++i){
        it_list = it_list->next;
    }
    ret = it_list->elem;
    return ret;
}

/*Leaves in the list the first n elemets and erase the others*/
list take(list l, unsigned int n){
    list basura;
    list it_list = l;
    for(unsigned int i = 0u; i < n; ++i){
        it_list = it_list->next;
    }
    basura = it_list->next;
    free(basura);
    it_list->next = NULL;
    return l;
}

/*Erase the first n elements of the list*/
list drop(list l, unsigned int n){
    list it_list;
    assert(length(l)>=n);
    for(unsigned int i = 0; i < n; ++i){
       it_list = l;
       l = l->next;
       free(it_list); 
    }
    return l;
}

/*Copies the list on an new list*/
list copy_list(list l){
    list new_list;
    list it_new_list;
    list it_list;
    if (l != NULL){
        it_new_list = malloc(sizeof(struct _node));
        it_list = l;
        new_list = it_new_list;
        while(it_list != NULL){
            it_new_list->elem = it_list->elem;
            it_new_list->next = malloc(sizeof(struct _node));
            it_new_list = it_new_list->next;
            it_list = it_list->next;
        }
        it_new_list->elem = it_list->elem;
        it_new_list->next = NULL;
    }
    else{
        new_list = NULL;
    }
    return new_list; 
}

//DESTROY

/*Free memeory*/
list destroy(list l){
    list p;
	while(!is_empty(l)){
		p = l;
		l = p->next;
		free(p);
	}
	return l;
}