#include <stdlib.h>
#include "fence.h"

struct _fence_t {
    fence_t next;
    type_t type;
};


fence_t fence_P(){
    fence_t new_fence = calloc(1, sizeof(struct _fence_t));
    new_fence->type = P;
    new_fence->next = NULL;
    return new_fence;
}
fence_t fence_add_P(fence_t fence){
    fence_t new_p = calloc(1, sizeof(struct _fence_t));
    new_p->type = P;
    new_p->next = NULL;
    if(fence != NULL){
        new_p->next = fence;
        fence = new_p;
    } 
    else{
        fence = new_p;
    }
    return fence;
}
fence_t fence_add_A(fence_t fence){
    fence_t new_a = calloc(1, sizeof(struct _fence_t));
    new_a->type = A;
    new_a->next = NULL;
    if(fence != NULL){
        new_a->next = fence;
        fence = new_a;
    } 
    else{
        fence = new_a;
    }
    return fence;
}
fence_t fence_add_H(fence_t fence){
    fence_t new_h = calloc(1, sizeof(struct _fence_t));
    new_h->type = H;
    new_h->next = NULL;
    if(fence != NULL){
        new_h->next = fence;
        fence = new_h;
    } 
    else{
        fence = new_h;
    }
    return fence;
}
fence_t fence_add_T(fence_t fence){
    fence_t new_t = calloc(1, sizeof(struct _fence_t));
    new_t->type = T;
    new_t->next = NULL;
    if(fence != NULL){
        new_t->next = fence;
        fence = new_t;
    } 
    else{
        fence = new_t;
    }
    return fence;
}
bool fence_is_correct(fence_t fence){
    bool tranquera = false;
    bool is_palo = true;
    fence_t f_aux = fence;
    if(f_aux->type == P){
        f_aux = f_aux->next;
        while(f_aux != NULL && is_palo){
            if(f_aux->type != P && f_aux->next->type != P){
                is_palo = false;
            } else if(f_aux->type != P && f_aux->next->type == P){ 
                if(f_aux->type == T){
                    tranquera = true;
                    f_aux = f_aux->next;
                } else{
                    f_aux = f_aux->next;
                }
            } else if(f_aux->type == P){
                f_aux = f_aux->next;
            }
        }
    } else{
        is_palo = false;
    }
    fence_destroy(f_aux);
    return tranquera && is_palo;
}
unsigned int fence_perimeter(fence_t fence){
    unsigned int elem_sum = 0;
    fence_t f_aux = fence;
    while(f_aux != NULL){
        if(f_aux->type != P){
            elem_sum = elem_sum + 3;
            f_aux = f_aux->next;
        } else{
            f_aux = f_aux->next;
        }
    }
    fence_destroy(f_aux);
    return elem_sum;
}
unsigned int fence_size(fence_t fence){
    unsigned int size = 0u;
    fence_t f_aux = fence;
    while(f_aux != NULL){
        ++size;
        f_aux = f_aux->next;
    }
    return size;
}
type_t *fence_to_array(fence_t fence){
    unsigned int size = fence_size(fence);
    fence_t f_aux = fence;
    type_t *array = NULL;
    if (f_aux != NULL){
        array = calloc(size,sizeof(type_t));
        for (unsigned int i = 0u; i < size; i++){
            array[i] = f_aux->type;
            f_aux = f_aux->next;
        }
    }
    return array;
}
fence_t fence_destroy(fence_t fence){
    fence_t f_aux = fence;
    while(fence != NULL){
        fence = fence->next;
        f_aux = fence;
    }
    free(f_aux);
    f_aux = NULL;
    return fence;
}