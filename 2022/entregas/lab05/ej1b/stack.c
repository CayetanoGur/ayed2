#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    size_t size;
    struct _s_stack * next;
};

static bool invrep(stack s){
    bool res = s != NULL;
    return res;
}

stack stack_empty() {
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));
    s->size = 0;
    s->next = NULL;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    stack new_elem = NULL;
    new_elem = malloc(sizeof(struct _s_stack));
    new_elem->elem = e;
    new_elem->size = s->size + 1u; 
    new_elem->next = s;
    assert(invrep(s));
    return new_elem;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    stack s_aux = s;
    size_t tmp = s->size;
    s = s->next;
    free(s_aux);
    s_aux = NULL;
    s->size = tmp - 1u;
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(invrep(s));
    unsigned int size;
    if(s == NULL){
        size = 0u;
    }else{
        size = s->size;
    }
    return size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) { 
   unsigned int len = stack_size(s);
    stack_elem *array = calloc(len, sizeof(stack_elem));
    stack iter = s;
    for (unsigned int i = len; i > 0; --i){
        array[i-1] = iter->elem;
        iter = iter->next;
    }     
    return array;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    stack s_aux = NULL;
    while (s != NULL) {
        s_aux = s;
        s = s->next;
        free(s_aux);
    }
    // free(s);
    // s = NULL;

    return s;
}



// #include <stdlib.h>
// #include <assert.h>
// #include <stdio.h>
// #include "stack.h"



// struct _s_stack{
//     struct _s_stack * next;
//     stack_elem elem;
//     size_t size;
// };

// static bool invrep(stack s){    
//  return s != NULL;
// }

// stack stack_empty(){
//     stack s = malloc(sizeof(struct _s_stack));
//     s->size = 0;
//     return s;
// }

// stack stack_push(stack s, stack_elem e){
//     //assert(invrep(s));
//     stack new_elem = malloc(sizeof(struct _s_stack));
//     new_elem->elem = e;
//     new_elem->size += 1;
//     new_elem->next = s;
    
//     return new_elem;
// }

// stack stack_pop(stack s){
//     assert(invrep(s));
//     stack erase = s;
//     s = s->next;
//     s->size = s->size - 1u;
//     free(erase);
//     erase = NULL;
//     return s;
// }

// /* falta hacer el size de orden constante */

// unsigned int stack_size(stack s){
//     //assert(invrep(s));
//     return s->size;
// }

// stack_elem stack_top(stack s){
//     assert(invrep(s));
//     return s->elem;
// }

// bool stack_is_empty(stack s){
//     //asstert(invrep(s));
//     return s->size == 0;
// }

// stack_elem *stack_to_array(stack s){
//     //assert(invrep(s));
    
//     stack_elem *array = calloc(s->size, sizeof(stack_elem));
//     stack iter = s;
//     for (unsigned int i = s->size; i > 0; --i){
//         array[i-1] = iter->elem;
//         iter = iter->next;
//     }     
//     return array;
// }


// stack stack_destroy(stack s){
//     assert(invrep(s));
//     stack aux_s = s;
//     stack trash;
//     while (aux_s->next != NULL){
//         trash = aux_s;
//         aux_s = aux_s->next;
//         free(trash);
//     }
//     free(aux_s);
//     aux_s = NULL;
//     return s;
// }

// stack print_stack(stack s){
//     stack it = s;
//     stack_elem top;
//     printf("[");
//     while(!stack_is_empty(it)){
//         top = stack_top(it);
//         it = it->next;
//         if (it != NULL)
//         {
//             printf("%d, ", top);
//         }else{
//             printf("%d", top);
//         }   
//     } 
//     printf("]");
//     return s;
// }