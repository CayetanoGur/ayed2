#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct _node {
    list_elem elem;
    list next;
};

list list_empty(){
    list l = malloc(sizeof(struct _node));
    l = NULL;
    return l;
}

list list_addl (list_elem e, list l){
    list newnode = malloc(sizeof(struct _node));
    newnode->elem = e;
    newnode->next = l;
    
    return newnode;
}

/* Destroy */

list list_destroy(list l){
    list p = NULL;
    p = l;
    while (!list_is_empty(p)){
        l = p;
        p = p->next;
        free(l);
    };
    l = NULL;
    return l;
}

/* Operation */
bool list_is_empty (list l){
    bool res = true;
    res = (l == list_empty());
    return res;
}

list_elem list_head (list l){
    assert(!list_is_empty(l));
    list_elem head;
    head = l->elem;
    return head;
}

list list_tail (list l){
    assert(!(list_is_empty(l)));
    list node_to_fst = NULL;
    node_to_fst = l;
    l = l->next;
    free(node_to_fst);
    node_to_fst = NULL;
    return l;
}

list list_addr (list l, list_elem e){
    list p = NULL;
    list node_rgt = malloc(sizeof(struct _node));
    node_rgt->elem = e;
    node_rgt->next = list_empty();
    p = l;
    if(!(list_is_empty(p))){
        while(!(list_is_empty(p->next))){
            p = p->next;
        };
        p->next = node_rgt;
    }
    else{
        l = node_rgt;
    }
    p = NULL;
    return l;
}

unsigned int list_length (list l){
    list p = NULL;
    p = l;
    unsigned int n = 0u;
    while(!(list_is_empty(p))){
        p = p->next;
        ++n;
    }
    p = NULL;
    return n;
}

list list_concat (list l, list l0){
    list aux = NULL;
    aux = l0;
    while(!(list_is_empty(aux))){
        l = list_addr(l, aux->elem);
        aux = aux->next;
    }
    free(aux);
    aux = NULL;
    return l;
}

list_elem list_index (list l, unsigned int n){
    list aux = NULL;
    aux = l;
    list_elem ret;
    unsigned int i = 0;

    while(i != n){
        aux = aux->next;
        ret = aux->elem;
        ++i;
    }

    free(aux);
    aux = NULL;
    return ret;
}

list list_take (list l, unsigned int n){
    list p = NULL;
    unsigned int length = list_length(l);
    unsigned int i = 0u;
    while(i <= length){
        if(i > n){
            p = l;
            l = p->next;
            free(p);
            ++n;
        }
        else{
            p = l;
            l = p->next;
            ++n;
        }
    }
    return l;
}

list list_drop (list l, unsigned int n){
    assert(n <= list_length(l));
    list p = NULL;
    unsigned int i = 0u;
    while (i < n){
        p = l;
        l = p->next;
        free(p);
        ++i;
    }
    return l;
}

list list_copy (list l, list l2){
    list p = NULL;
    l2 = list_empty();
    p = l;
    while(!(list_is_empty(p))){
        l2 = list_addr(l2, p->elem);
        p = p->next;
    }
    return l2;
}

