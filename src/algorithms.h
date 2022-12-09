#pragma once

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "transit.h"

using namespace std;


class Algorithm {
public:
    /** @brief Parametrized constructor for algorithm.
     *         Constructs a graph with a given vector of vertices and
     *         edges.
     * 
     *  @param vertices_ vector of vertices parsed from dataset.
     *  @param edges_ vector of edges parsed from dataset.
    */
    Algorithm(vector<Vertex> vertices_, vector<Edge> edges_);

    /** @brief Fills the graph with information about the edges.
     *         This will end up connecting the vertices in the graph.
     */
    void buildGraph();

    /** @brief Getter for graph.
     * 
     *  @return graph.
     h*/
    map<Vertex, map<Vertex, vector<Edge>>>& getGraph();

private:
    /** @brief Default constructor for Algorithm.
     *         This is private because we don't want this to be used.
     */
    Algorithm() { /* Do nothing. */ }


    /* 
     * This is an weighted, directed adjacency matrix.
     * This constitutes the graph of stops (Vertices) and routes (Edges).
     */
    map<Vertex, map<Vertex, vector<Edge>>> graph;

    /* 
     * Represents all stops (Vertices).
     */
    vector<Vertex> vertices;

    /* 
     * Represents all routes (Edges).
     */
    vector<Edge> edges;
};
