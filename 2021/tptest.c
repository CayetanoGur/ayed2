#include <stdio.h>
#include <stdlib.h>


void swap(int a[], unsigned int x, unsigned int y){
    unsigned int aux;
    aux = a[x];
    a[x] = a[y];
    a[y] = aux;  
    
}




void alg_q (int a[], unsigned int x){
    unsigned int m;
    for(unsigned int j = 0; j<=x; ++j){
        m = j;
        for(unsigned int k = j+1; k<= x; ++k){
            if(a[k]<a[m]){
                m = k;
            }
        }
        swap(a,j,m);
    }
}




int main (void){
    unsigned int length;
    unsigned int x;
    // int y;
    printf("ingrese largo del arreglo \n");
    scanf("%u", &length);
    int a[length];
    for (unsigned int i = 0;i < length; i++){
        unsigned int elem;
        scanf("%u", &elem);
        a[i] = elem;
    }
    printf("ingrese x \n");
    scanf("%u", &x);
    // printf("ingrese y \n");
    // scanf("%d", y);

    alg_q(a,x);
    for(unsigned int i=0; i<length; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}