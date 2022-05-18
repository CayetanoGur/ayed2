#include <stdio.h>

void absolute(int x, int *y) {
    if(x >= 0){
    	*y = x;
    }
    else{
    	*y = -x;
    }
}

int main(void) {
	int res = 0;
    int a = -89	;
    absolute(a, &res);
    printf("%d\n", res);
    return 0;
}

