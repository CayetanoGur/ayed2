#include <assert.h>
#include "change_making.h"
#include "amount.h"
#include "set.h"
#include "currency.h"


/** Change-Making Algorithm
@param charge    A given price money to pay with coins
@param coins     A set of coin denominations

@return The minimun amount of coins needed for pay the charge
*/

amount_t min(amount_t a, amount_t b){
    amount_t min = a;
    if(amount_lt(b, a)){
        min = b;
    }
    return min;
}

amount_t change_making(currency_t charge, set coins) {
    coin_t coin;
    amount_t result = amount_inf();
    set copy_coins = set_empty();
    if(charge == 0u){
        result = charge;
    } else if(set_is_empty(coins)){
        result = amount_inf();
    } else{
        copy_coins = set_clone(coins);
        coin = set_get(coins);
        copy_coins = set_elim(copy_coins, coin);
        if(amount_le(coin, charge) && coin != 0u){
            result = min(amount_sum(1, change_making(charge - coin, coins)), change_making(charge, copy_coins));
        } else{
            result = change_making(charge, copy_coins);
        }
        copy_coins = set_destroy(copy_coins);
    }

    return result;
}
