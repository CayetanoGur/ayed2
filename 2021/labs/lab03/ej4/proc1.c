#include <stdio.h>

void absolute(int x, int y) {
    if (x>=0){
        y = x;
    }
    else{
        y = -x;
    }
}

int main(void) {
    
    int a, res;
    res = 0;
    a = -98;
    absolute(a,res);
    printf("El valor abs de %d es: %d \n", a, res);
    
    return 0;
}

