#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



typedef int list_elem;
typedef struct _node * list;

//CONSTRUCTORS

/*Creates empty list*/
list empty();

/*adds an element at the left of the list*/
list addl(list_elem e, list l);

//OPERATIONS

/*Returns True if the list is empty*/
bool is_empty(list l);

/*Return the first element of the list*/
list_elem head(list l);

/*Erase the first element of the list*/
list tail(list l);

/*Adds an element to the right of the list*/
list addr(list l, list_elem e);

/*Returns the lenght of the list as an unsigned int type*/
unsigned int length (list l);

/*Returns the concatenation of two lists*/
list concat(list l0, list l1);

/*Returns the index n of a list.
PRE: length(l)>n*/
list_elem index(list l, unsigned int n);

/*Leaves in the list the first n elemets and erase the others*/
list take(list l, unsigned int n);

/*Erase the first n elements of the list*/
list drop(list l, unsigned int n);

/*Copies the list on an new list*/
list copy_list(list l);

//DESTROY

/*Free memeory*/
list destroy(list l);

#endif