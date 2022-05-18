#include <stdlib.h>
#include <assert.h>
#include "item.h"
#include "knapsack.h"
#include "set.h"

struct _s_knap {
    set packed_items;
    weight_t capacity;
    weight_t weight;
    value_t value;
};


static bool invrep(knapsack k) {
    return (k->capacity >= k->weight);
}

knapsack knapsack_empty(weight_t capacity) {
    knapsack new = calloc(1, sizeof(struct _s_knap));
    new->packed_items = set_empty();
    new->capacity = capacity;
    new->weight = 0u;
    new->value = 0u;
    assert(invrep(new));
    return new;
}

knapsack knapsack_clone(knapsack k) {
    assert(invrep(k));
    knapsack clone = knapsack_empty(k->capacity);
    clone->packed_items = set_clone(k->packed_items);
    clone->weight = k->weight;
    clone->value = k->value;
    assert(invrep(clone));
    return clone;
}

knapsack knapsack_pack(knapsack k, item_t item) {
    assert(invrep(k) && knapsack_can_hold(k, item));
    k->packed_items = set_add(k->packed_items, item);
    k->weight = k->weight + item_weight(item);
    k->value = k->value + item_value(item);
    assert(invrep(k));
    return k;
}

bool knapsack_greater_value(knapsack k1, knapsack k2) {
    assert(invrep(k1) && invrep(k2));
    return (k1->value > k2->value);
}

bool knapsack_is_full(knapsack k) {
    assert(invrep(k));
    return (k->capacity == k->weight);
}

bool knapsack_can_hold(knapsack k, item_t item) {
    assert(invrep(k));
    return(k->capacity >= (k->weight + item_weight(item)));
}

weight_t knapsack_capacity(knapsack k) {
    assert(invrep(k));
    return k->capacity;
}

weight_t knapsack_weight(knapsack k) {
    assert(invrep(k));
    return k->weight;
}

value_t knapsack_value(knapsack k) {
    assert(invrep(k));
    return k->value;
}

void knapsack_dump(knapsack k) {
    weight_t capacity, remind;
    assert(invrep(k));
    capacity = knapsack_capacity(k);
    remind = capacity - knapsack_weight(k);
    printf("knapsack value   : $%u\n", knapsack_value(k));
    printf("knapsack capacity: %u\n", capacity);
    printf("knapsack remind  : %u\n", remind);
    printf("**** packed items ****\n");
    set_dump(k->packed_items);
}

knapsack knapsack_destroy(knapsack k) {
    assert(invrep(k));
    k->packed_items = set_destroy(k->packed_items);
    free(k);
    k = NULL;
    return k;
}

