#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "amount.h"


// static bool invrep(amount_t a){
//     bool res = true;
//     if(!amount_is_inf(a)){
//         res = amount_le(a, amount_inf) == true && amount_is_inf(amount_sum(a, amount_inf()) == true);
//     }
//     else{
//         res = amount_is_inf(amount_inf()) == true;
//     }
    
//     return res;
// };

amount_t amount_inf(){
    amount_t a;
    a = 0u - 1u;
    //assert(invrep(a));
    return a; 
}

bool amount_is_inf(amount_t a){
    //assert(invrep(a));
    return a == 0u - 1u;
}

bool amount_le(amount_t a1, amount_t a2){
    //assert(invrep(a1)&&invrep(a2));
    return a1 <= a2;
}

bool amount_lt(amount_t a1, amount_t a2){
    //assert(invrep(a1)&&invrep(a2));
    return a1 < a2;
}

amount_t amount_sum(amount_t a1, amount_t a2){
    //assert(invrep(a1)&&invrep(a2));
    if(amount_is_inf(a1) || amount_is_inf(a2)){
        return amount_inf();
    }
    else{
        return a1 + a2;
    }
}

void amount_dump(amount_t a){
    
    if (amount_is_inf(a)) {
        printf("#");
    } else {
        printf("%u", a);
    }
}
