#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to structs to guarantee encapsulation */
typedef struct _node * list;

typedef int list_elem;

/* Constructors */
list empty(void);
/*
    Creates a new empty list.
    Being l the returned list, is_empty(l) should be true.
*/

list addl(list l, list_elem e);
/*
    Adds the element e to the start of the list.
*/


/* Operations */
bool is_empty(list l);
/*
    Return whether the list l is empty.
*/

list_elem head(list l);
/*
    Returns the first element of the list l.
*/

list tail(list l);
/*
    Deletes the first element of the list l and returns the rest.
    PRECONDITION: !is_empty(list l)
*/

list addr(list l, list_elem e);
/*
   Adds the element e at the end of the list.
*/

unsigned int length(list l);
/*
   Returns the amount of elements on the list l.
*/

list concat(list l, list l0);
/*
   Adds the element of the list l0 to the list l in the same order.
*/

list_elem index(list l, unsigned int n);
/*
   Returns the element in the nth position of the list.
   PRECONDITION: len(l) > n
*/

list take(list l, unsigned int n);
/*
   Keeps the first n elements of the list l, deleting the rest.
*/

list drop(list l, unsigned int n);
/*
   Deletes the first n elements of the list l.
*/

list copy_list(list l);
/*
   Copies all the elements of the list l and stores them in a new list.
*/

/* Destroy */
list list_destroy(list l);
/*
   Frees memory for l.	
*/

#endif