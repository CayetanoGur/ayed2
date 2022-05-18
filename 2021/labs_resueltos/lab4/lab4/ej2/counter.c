#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"
#include <assert.h>

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
	counter new_counter;
	new_counter = malloc(sizeof(struct _counter));
	new_counter->count = 0;
	return new_counter;
}

void counter_inc(counter c) {
	c->count = c->count + 1;
}

bool counter_is_init(counter c) {
	return (c->count == 0);
}

void counter_dec(counter c) {
	assert(!counter_is_init(c));
	c->count = c->count - 1;
}

counter counter_copy(counter c) {
	counter copy;
	copy = counter_init();
	copy->count = c->count;
	return copy;
}

void counter_destroy(counter c) {
	free(c);
	c = NULL;
}
