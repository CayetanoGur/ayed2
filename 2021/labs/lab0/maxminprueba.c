#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define ARRAY_SIZE 10

struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

struct max_min_result compute_max_min(int array[], unsigned int length)
{
    assert(length > 0);
    //array = array;
    struct max_min_result result = { array[0], array[0], 0, 0 };

    for (unsigned int i = 0; i < length; ++i)
        {
            if (array[i] > result.max_value && array[i] >= result.min_value)
            {
                result.max_value = array[i];
                result.max_position = i;
            }
            else if (array[i] < result.min_value && array[i] <= result.max_value)
            {
                result.min_value = array[i];
                result.min_position = i;
            }
        }
    return result;
}

void pedirArreglo(int a[], int n_max)
{
    int i, elem;
    i = 0;

    while (i < n_max)
    {
        printf("Ingrese el elemento de la posicion %d\n", i);
        scanf("%d", &elem);
        a[i] = elem;
        i = i + 1;
    }
    
}
int pedirEntero(void)
{
	int x;
	scanf("%d",&x);
	return x;
}

int main()
{
    int array[ARRAY_SIZE];   
    printf("Ingrese el tamaño del arreglo\n");
    int N = pedirEntero();
    pedirArreglo(array, N);

    struct max_min_result result = compute_max_min(array, N);
    printf("Máximo: %d\n", result.max_value);
    printf("Posición del máximo: %u\n", result.max_position);
    printf("Mínimo: %d\n", result.min_value);
    printf("Posición del mínimo: %u\n", result.min_position);
    return 0;
}
