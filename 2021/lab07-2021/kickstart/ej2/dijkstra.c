#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"


cost_t *dijkstra(graph_t graph, vertex_t init) {
    unsigned int max_vert = graph_max_vertexs(graph);
    assert(init < max_vert);

    set C = set_empty();
    for(vertex_t i = 0; i < max_vert; ++i){
        C = set_add(C,i);
    }
    C = set_elim(C, init);
}
