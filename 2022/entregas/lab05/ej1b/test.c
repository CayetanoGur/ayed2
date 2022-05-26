#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

static void array_dump(int a[], unsigned int length) {
    fprintf(stdout, "[");
    for (unsigned int i = 0u; i < length; ++i) {
        fprintf(stdout, "%d", a[i]);
        if (i < length - 1) {
            fprintf(stdout, ", ");
        } else {
            fprintf(stdout, "]\n");
        }
    }
}

int main(void){
    stack s = stack_empty();
    s = stack_push(s, 0);
    s = stack_push(s, 1);
    s = stack_push(s, 2);
    s = stack_pop(s);
    s = stack_push(s, 2);
    s = stack_push(s, 3);
    s = stack_push(s, 4);
    unsigned int size = stack_size(s);
    stack_elem top = stack_top(s);
    printf("Size: %u \n", size);
    printf("Top: %d \n", top);
    //s = print_stack(s);
    printf("\n");
    
    stack_elem *array = stack_to_array(s);
    array_dump(array, size);
    stack_destroy(s);
    return 0;
}