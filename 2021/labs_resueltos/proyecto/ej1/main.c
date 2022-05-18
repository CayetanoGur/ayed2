#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "amount.h"
#include "set_elem.h"

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
    	if(amount_le(coin, charge)){
            result = min(amount_sum(1, change_making(charge - coin, coins)), change_making(charge, copy_coins));
    	} else{
    		result = change_making(charge, copy_coins);
    	}
    	copy_coins = set_destroy(copy_coins);
    }
    return result;
}


int main(){
	set new_set = set_empty();
	new_set = set_add(new_set, 1);
	new_set = set_add(new_set, 5);
	new_set = set_add(new_set, 10);
	set clone = set_clone(new_set);
	amount_t result = change_making(75, new_set);
	amount_dump(result);
	clone = set_destroy(clone);
	new_set = set_destroy(new_set);

}
