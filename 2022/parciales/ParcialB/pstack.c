#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node * node;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node * next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node->next);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool res;
    res = s != NULL;
    return res;
}

pstack pstack_empty(void) {
    pstack s = malloc(sizeof(struct s_pstack));
    s->size = 0u;
    s->node = NULL;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    pstack iterator = s;
    while(new_node->priority <= iterator->node->priority){
        iterator->node = iterator->node->next;
    }
    new_node->next = iterator->node->next;
    iterator->node->next = new_node;
    s = iterator;
    s->size = s->size + 1;

    //assert(e==e && priority==priority && new_node==new_node); BORRAR ESTE ASSERT
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(s==s);
    return s->node->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s));
    return s->node->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    pstack aux = s;
    s->node = s->node->next;
    free(aux);
    aux = NULL;
    s->size = s->size - 1;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    
    
    assert(s == NULL);
    return s;
}

