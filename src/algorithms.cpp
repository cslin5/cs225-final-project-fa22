#include <algorithm>

#include "algorithms.h"


/** @brief Default constructor for Algorithm.
 */
Algorithm::Algorithm(vector<Vertex> vertices_, vector<Edge> edges_) : 
        vertices(vertices_), edges(edges_) {
    /* Do something. */
    buildGraph();
}

/** @brief Fills the graph with information about the edges.
 *         This will end up connecting the vertices in the graph.
 */
void Algorithm::buildGraph() {
    for (Edge edge : edges) {
        graph[edge.origin][edge.destination].push_back(edge);
    }
}

map<Vertex, map<Vertex, vector<Edge>>>& Algorithm::getGraph() {
    return graph;
}