#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "amount.h"


amount_t amount_inf()
{
	return UINT_MAX;
}

bool amount_is_inf(amount_t a)
{
	return (a == amount_inf());
}

bool amount_le(amount_t a1, amount_t a2)
{
	return a1 <= a2;
}

bool amount_lt(amount_t a1, amount_t a2)
{
	return a1 < a2;
}

amount_t amount_sum(amount_t a1, amount_t a2)
{	
	amount_t sum = a1 + a2;
	//After computing the sum we check if the result is less than a1 or a2, since we're dealing with unsigned numbers in the case of overflow
	//the result will be lesser than either of the operands
	if(sum < a1){
		sum = amount_inf();
	}
	return sum;
}

void amount_dump(amount_t a)
{
    if (amount_is_inf(a)) {
        printf("#");
    } else {
        printf("%d", a);
    }
}