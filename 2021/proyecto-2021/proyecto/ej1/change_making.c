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
//TODO: HACER INVREP

// static amount_t minimun (amount_t a, amount_t b){
//     amount_t res;
//     if(amount_le(a,b)){
//         res = a;
//     }
//     else{
//         res = b;
//     }
//     return res;
// }

amount_t change_making(currency_t charge, set coins) {
    amount_t res;
    set_elem c;
    set c_aux = set_empty();
    if (charge == 0){
        res = 0u;
    } else if (set_is_empty(coins)){
        res = amount_inf();
    }
    else{
        c_aux = set_clone(coins);
        c = set_get(coins);
        c_aux = set_elim(c_aux,c);
        if(amount_le(c,charge)){
            if(amount_le(amount_sum(1u, change_making(charge-c, coins)), change_making(charge,coins))){
                res = 1u + change_making(charge - c, coins);
            } 
            else{
                res = change_making(charge, c_aux);
            }
        }
        else{
            res = change_making(charge, c_aux);
        }
    }
    c_aux = set_destroy(c_aux);
    return res;
}

/*
amount_t change_making(currency_t charge, set coins) {
    amount_t res = 0u;
    set_elem c;
    set c_aux = set_empty();
    if (charge == 0){
        res = 0U;
    } else if (set_is_empty(coins)){
        res = amount_inf();
    }
    else{
        c_aux = set_clone(coins);
        c = set_get(coins);
        c_aux = set_elim(c_aux,c);
        if(amount_le(c,charge)){
            res = minimun(amount_sum(1, change_making(charge-c,coins)),change_making(charge,coins));
        else{
            res = change_making(charge, c_aux);
        }
    }

    c_aux = set_destroy(c_aux);
    return res;
}
*/