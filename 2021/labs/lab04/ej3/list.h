#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
/*TAD LISTAS*/

/* Constructores */
typedef int list_elem;

typedef struct _node *list;


list list_empty(void);

list list_addl (list_elem e, list l);

/* Destroy */

list list_destroy(list l);

bool list_is_empty (list l);

list_elem list_head (list l);

list list_tail (list l);

list list_addr (list l, list_elem e);

unsigned int list_length (list l);

list list_concat (list l, list l0);

list_elem list_index (list l, unsigned int n);

list list_take (list l, unsigned int n);

list list_drop (list l, unsigned int n);

list list_copy (list l, list l2);

#endif