#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c = malloc(sizeof(struct _counter));
    c->count = 0;
    assert(c->count == 0);
    return c;
}

void counter_inc(counter c) {
    ++c->count;
}

bool counter_is_init(counter c) {
    return c->count == 0u;
}

void counter_dec(counter c) {
    assert(c->count != 0); // mejor hacer un if aca que devuelva un msj
    --c->count;
}

counter counter_copy(counter c) {
    counter aux;
    aux =  counter_init();
    //aux = c esto esta pesimo porque cada vez que modifico aux modifico c ya que estan apuntando al mismo espacio de memoria y ademas el malloc fue al vicio, es un memory leak.
    aux->count = c->count;
    return aux;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}
