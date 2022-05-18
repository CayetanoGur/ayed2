#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "cost.h"

struct graph_data {
    cost_t *costs;
    unsigned int max_vertexs;
};

static unsigned int g_index(vertex_t i, vertex_t j, unsigned int max_vertexs) {
    return j + (i * max_vertexs);
}

static bool invrep(graph_t g) {
    bool is_graph = (g != NULL);
    if (is_graph){
        is_graph = (g->costs != NULL);
    }
    return is_graph;
}

graph_t graph_empty(unsigned int max_vertexs)
{
    graph_t graph = calloc(1, sizeof(struct graph_data));
    assert(graph != NULL);
    graph->max_vertexs = max_vertexs;
    // Create adjacency matrix for graph
    graph->costs = calloc(max_vertexs * max_vertexs, sizeof(cost_t));
    if (graph->costs != NULL){
         // Save matrix in the structure
        for (unsigned int i = 0u; i < max_vertexs * max_vertexs; ++i) {
            graph->costs[i] = cost_inf();
        }
    } else {
        fprintf(stderr, "Error: No hay suficiente memoria. \n");
        exit(EXIT_FAILURE);
    }
    assert(invrep(graph) && graph->costs != NULL);
    return graph;
}

unsigned int graph_max_vertexs(graph_t graph)
{
    assert(graph != NULL);
    return graph->max_vertexs;
}

void graph_add_edge(graph_t graph, vertex_t from, vertex_t to, cost_t cost)
{
    assert(graph != NULL);
    assert(from < graph->max_vertexs);
    assert(to < graph->max_vertexs);
    unsigned int index = g_index(from, to, graph->max_vertexs);
    graph->costs[index] = cost;
    assert(invrep(graph));
}

cost_t graph_get_cost(graph_t graph, vertex_t from, vertex_t to)
{
    assert(graph != NULL);
    assert(from < graph->max_vertexs);
    assert(to < graph->max_vertexs);
    unsigned int index= g_index(from, to, graph->max_vertexs);
    cost_t costs = graph->costs[index];
    return costs;
}

graph_t graph_destroy(graph_t graph)
{
    assert(graph != NULL);
    free(graph->costs);
    free(graph);
    graph = NULL;
    assert(graph == NULL);
    return graph;
}

void graph_print(graph_t graph)
{
    assert(graph != NULL);
    printf("%u\n", graph->max_vertexs);
    for (unsigned int i = 0; i < graph->max_vertexs; ++i) {
        for (unsigned int j = 0; j < graph->max_vertexs; ++j) {
            const cost_t cost = graph_get_cost(graph, i, j);
            if (cost_is_inf(cost)) {
                printf("# ");
            } else {
                printf("%d ", cost);
            }
        }
        printf("\n");
    }
}

graph_t graph_from_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int tam = 0;
    fscanf(file, " %u ", &tam);
    char word[256];
    const graph_t graph = graph_empty(tam);
    for (unsigned int i = 0; i < tam; ++i) {
        for (unsigned int j = 0; j < tam; ++j) {
            cost_t cost = cost_inf();
            fscanf(file, " %s ", word);
            if (word[0] != '#') {
                cost = atoi(word);
            }
            graph_add_edge(graph, i, j, cost);
        }
    }
    fclose(file);
    return graph;
}
