#include <algorithm>

#include "algorithms.h"


Algorithm::Algorithm(vector<Vertex> vertices_, vector<Edge> edges_) : 
        vertices(vertices_), edges(edges_) {
    buildGraph();
}

void Algorithm::buildGraph() {
    for (Edge edge : edges) {
        graph[edge.origin][edge.destination].push_back(edge);
    }
}

map<Vertex, map<Vertex, vector<Edge>>>& Algorithm::getGraph() {
    return graph;
}