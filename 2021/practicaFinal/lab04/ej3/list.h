#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/*List as a linked list with pointers*/
typedef struct _list * list;
typedef unsigned int elem;

/*Constructors*/

list empty_list(void);
/*Create an empty list*/

list addl_list(list l, elem e);
/*Adds an element e at the beginnig of the list*/

#endif