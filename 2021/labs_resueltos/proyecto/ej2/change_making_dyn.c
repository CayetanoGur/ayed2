#include <stdlib.h>
#include <stdio.h>
#include "currency.h"
#include "amount.h"

/** Change-Making Dynamic
@param charge    A given price money to pay with coins
@param coins     An array of coin denominations

@return The minimun amount of coins needed for pay the charge

*/


void create_matrix(amount_t ***pointer, unsigned int rows, unsigned int columns){
    amount_t **matrix = calloc(rows + 1, sizeof(amount_t*));
    if(matrix == NULL){
        fprintf(stderr, "Error: No hay suficiente memoria.\n");
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0u; i <= rows; i++){
        matrix[i] = calloc(columns + 1, sizeof(amount_t));
        if(matrix[i] == NULL){
            fprintf(stderr, "Error: No hay suficiente memoria.\n");
            exit(EXIT_FAILURE);
        }
    }
    *pointer = matrix;
}

void destroy_matrix(amount_t **matrix, unsigned int rows){
    for(unsigned int i = 0u; i <= rows; i++){
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}

amount_t min_amount_t(amount_t a, amount_t b){
    amount_t min = a;
    if(amount_lt(b, a)){
        min = b;
    }
    return min;
}

amount_t change_making_dyn(currency_t charge, coin_t *coins, unsigned int n_coins) {
    amount_t **matrix = NULL;
    amount_t result = 0;
    create_matrix(&matrix, n_coins, charge);
    for(unsigned int i = 0u; i <= n_coins; i++){
        matrix[i][0] = 0;
    }
    for(currency_t j = 1u; j <= charge; j++){
        matrix[0][j] = amount_inf();
    }
    for(unsigned int i = 1u; i <= n_coins; i++){
        for(currency_t j = 1u; j <= charge; j++){
            if(amount_lt(j, coins[i - 1u]) || coins[i - 1u] == 0u){
                matrix[i][j] = matrix[i-1][j];
            } else{
                matrix[i][j] = min_amount_t(matrix[i-1][j], amount_sum(1, matrix[i][j-coins[i - 1u]]));
            }
        }
    }
    result = matrix[n_coins][charge];
    destroy_matrix(matrix, n_coins);
    return result;
}
