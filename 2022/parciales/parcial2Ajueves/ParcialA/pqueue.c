#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *node;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep_node(struct s_node * node){
    bool valid = true;
    if(node != NULL){
        valid = true;
        if(node->next != NULL){
            while (node->next->next != NULL){
                valid = valid  && node->priority <= node->next->priority;
                node = node->next;
            } 
        }
    }
    return valid;
}

static bool invrep(pqueue q) {
    // las prioridadaes se mantengan
    // la cant de elementos se igual al size
    // si q->node es null size tiene que ser 0
    bool valid = q != NULL && invrep_node(q->node);
    return valid;
}

pqueue pqueue_empty(void) {
    pqueue q = malloc(sizeof(struct s_pqueue));
    q->node = NULL;
    q->size = 0u;
    assert(invrep(q)); 
    return q;
}




pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);

    if(q->node == NULL){
        q->node = new_node;
    } else if (priority < q->node->priority){
        new_node->next = q->node;
        q->node = new_node;
    } else {
        struct s_node *it = q->node;
        while(it->next != NULL && priority >= it->next->priority){
            it = it->next;
        }
        new_node->next = it->next;
        it->next = new_node;
    }
    q->size++;
    

    // struct s_node * it = q->node;
    // struct s_node * aux = NULL;
    // //si no hay elementos lo encolo al principio
    // if (q->node == NULL){
    //     q->node = new_node;
    // }else{
    //     //itero hasta que haya un lugar con la prioridad correcta o hasta que se acabe la queue
    //     while(it->priority <= priority &&  it->next != NULL){
    //         aux = it;
    //         it = it->next;
    //     }
    //     if(it != NULL && aux != NULL){
    //         aux->next = new_node;
    //         new_node->next = it;
    //     }
    //     else if(it == NULL && aux->next == NULL){
    //         aux->next = new_node;
    //     }
    //     else if(aux == NULL){
    //         new_node->next = q->node;
    //         q->node = new_node;
    //     }
    // }
    // q->size = q->size + 1;
    assert(invrep(q));
    return q;
}



bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0u;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q));
    pqueue_elem peek = q->node->elem;
    return peek;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int priority = q->node->priority;
    return priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q));
    struct s_node *garbage = q->node;
    q->node = q->node->next;
    garbage = destroy_node(garbage);
    q->size = q->size - 1;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while (q->node != NULL){
        struct s_node *garbage;
        garbage = q->node;
        q->node = q->node->next;
        garbage = destroy_node(garbage);
    }
    q->node = NULL;
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
