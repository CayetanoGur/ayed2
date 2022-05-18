#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(void){
    stack new_stack = stack_empty();
    stack_elem elem = 9;
    stack_elem top;
    new_stack = stack_push(new_stack, elem); 
    top = stack_top(new_stack);
    new_stack = stack_pop(new_stack);
    
    return 0;
}