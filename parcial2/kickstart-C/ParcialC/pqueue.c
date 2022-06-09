#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

//para no hacer realloc todo el tiempo, me fijo en el archivo de input cuantas prioridades voy a tener y pido memoria para esa cantidad de colas
//hacer el size constante
struct s_pqueue {
    unsigned int size;
    struct s_node ** array;
    priority_t min;
};

struct s_node {
    unsigned int size;
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pqueue q) {
    return q != NULL;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue queue = malloc(sizeof(struct s_pqueue));
    queue->size = 0u;
    queue->array = calloc(min_priority+1,sizeof(struct s_node));
    queue->min = min_priority;
    assert(invrep(queue) && pqueue_is_empty(queue));
    return queue;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node * new_node = create_node(e);

    struct s_node * it = q->array[priority];
    if(it == NULL){
        it = new_node;
    }
    //estoy teniendo problema en encolar elementos con la misma prioridad, piso la cola y directamente dejo el ultimo elemento
    else{
        while(it->next != NULL){
            it = it->next;
        }
        //it->next = malloc(sizeof(struct s_node));
        it->next = new_node;
    }
    q->array[priority] = it;
    q->size = q->size + 1;

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0u; 
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem ret;
    pqueue it = q;
    priority_t i = 0u;
    while(it->array[i] == NULL){
        ++i;
    }
    ret = it->array[i]->elem;
    return ret;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue it = q;
    priority_t i = 0u;
    while(it->array[i] == NULL){
        ++i;
    }
    return i;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size; 
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue it = q;
    priority_t i = 0u;
    while(it->array[i] == NULL){
        ++i;
    }
    struct s_node *basura = it->array[i];
    it->array[i] = it->array[i]->next;
    destroy_node(basura);
    it->size = it->size - 1;
    q = it;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    for (unsigned int i = 0; i < q->min; ++i){
        if (q->array[i] != NULL){
            struct s_node *garbage;
            while (q->array[i] != NULL){
                garbage = q->array[i];
                q->array[i] = q->array[i]->next;
                destroy_node(garbage);
            }
        }  
    }
    free(q->array);
    q->array = NULL;
    free(q);
    q = NULL;
    
    return q;
}

