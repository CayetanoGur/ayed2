#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"


unsigned int min(unsigned int a, unsigned int b){
	unsigned int min;
	if(a > b){
		min = b;
	} else {
		min = a;
	}
	return min;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
    set set_aux = set_empty();
    vertex_t vertex_aux;
    unsigned int size = graph_max_vertexs(graph);
    cost_t *costs = calloc(size, sizeof(cost_t));
    for(unsigned int i = 0u; i < size; i++){
    	if(i != init){
    		set_aux = set_add(set_aux, i);  //Initialize set_aux
    	}
    }
   	for(unsigned int i = 0u; i < size; i++){
   		costs[i] = graph_get_cost(graph, init, i);  //Initialize costs
   	}
    while(!set_is_empty(set_aux)){
    	vertex_aux = set_get(set_aux);
   		for(unsigned int i = 0u; i < size; i++){  //Get the set member c so that the index c in costs has the minimum value (costs[c])
    		if(set_member(i, set_aux) && costs[i] < costs[vertex_aux]){ 
    			vertex_aux = i;
    		}
    	}
   		set_aux = set_elim(set_aux, vertex_aux);
   		for(unsigned int i = 0u; i < size; i++){
   			if(i != init){
   				costs[i] = min(costs[i], costs[vertex_aux] + graph_get_cost(graph, vertex_aux, i)); //Calculate minimum path cost.
   			}
   		}
   	}
   	set_aux = set_destroy(set_aux);
   	return costs;
}
