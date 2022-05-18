#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main(){
    stack test = stack_empty();
    stack_elem elem = 9;
    stack_elem elem2 = 2;
    stack_elem elem3 = 3;
    stack_elem top;
    test = stack_push(test, elem);
    unsigned int length = stack_size(test);
    printf("length: %d \n", length);
    top = stack_top(test);
    printf("top: %d \n", top);
    test = stack_push(test, elem2);
    top = stack_top(test);
    printf("top: %d \n", top);
    test = stack_push(test, elem3);
    top = stack_top(test);
    printf("top: %d \n", top);
    length = stack_size(test);
    printf("length: %d \n", length);
    test = stack_pop(test);
    length = stack_size(test);
    printf("length: %d \n", length);

    return 0;
}