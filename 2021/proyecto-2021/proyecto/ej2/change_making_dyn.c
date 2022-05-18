#include <stdlib.h>
#include <stdio.h>
#include "currency.h"
#include "amount.h"

/** Change-Making Dynamic
@param charge    A given price money to pay with coins
@param coins     An array of coin denominations

@return The minimun amount of coins needed for pay the charge

*/
static unsigned int minimun (unsigned int a, unsigned int b){
    return ((a < b) ? a : b);
}
//*coins lo trato como un arreglo
amount_t change_making_dyn(currency_t charge, coin_t *coins, unsigned int n_coins) {
    //cost_t* costs_array = calloc(max_vertexs * max_vertexs, sizeof(cost_t));
    //amount_t** matrix[charge][n_coins];
    amount_t res;
    amount_t** matrix = calloc(n_coins+1,sizeof( amount_t*));

    for(unsigned int i = 0u; i<=charge; ++i){
        matrix[i][0] = 0u;
    }
    for(unsigned int j = 0u; j<= n_coins; ++j){
        matrix[0][j] = amount_inf();
    }
    for(unsigned int i = 1u; i<=charge; ++i){
        for(unsigned int j = 1u; j<= n_coins; ++j){
            if(coins[i-1] > j){
                matrix[i][j] = matrix[i-1][j];
            }
            else{
                matrix[i][j] = minimun(matrix[i-1][j],amount_sum(1,matrix[i][j-coins[i]]));
            }
        }
    }
    res = matrix[charge][n_coins];
    free(matrix);
    matrix = NULL;

    return res;
}

