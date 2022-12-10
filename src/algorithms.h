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

    // Constructor

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


    // Getters

    /** @brief Getter for graph.
     * 
     *  @return graph.
     */
    map<Vertex, map<Vertex, vector<Edge>>>& getGraph();


    // DFS to find connected vertices through routes


    bool RouteConnection(string route, Vertex origin, Vertex destination);

    Edge findEdge(string route, Vertex origin, Vertex destination);

    // Dijkstra's Algorithm

    /** @brief Dijkstra's Algorithm.
     *         This is an algorithm for finding the shortest paths between
     *         vertices in the graph.
     * 
     *         Here, it will be used to find the path of least time between
     *         two vertices.
     */
    map<Vertex, double> Dijkstra(Vertex source);

    /** @brief Finds all edges with origin at vertex.
     * 
     *  @param vertex source.
     *  @return a vector of edges.
     */
    vector<Edge> findOutgoingEdges(Vertex vertex);
    
    /** @brief Finds all edges with destination at vertex.
     * 
     *  @param vertex destination.
     *  @return a vector of edges.
     */
    vector<Edge> findIncomingEdges(Vertex vertex);

    /** @brief Returns the 
     * 
     *  @param intervals Vector for the min time difference for each
     *         vertex.
     *  @param visited Vector to mark vertices as visited or unvisited.
     *  @return the min time difference.
     */
    int minInterval(vector<double> intervals, vector<bool> visited);

    /** @brief Finds the index of vertex in vertices.
     * 
     *  @param vertex Vertex to be found.
     *  @return index of vertex to be found.
    */
    int findVertexIndex(Vertex vertex);


    // Tarjan's Algorithm

    /** @brief Tarjan's Algorithm.
     *         This is an algorithm used to find the strongly connected
     *         components of a graph.
     * 
     *  @return the number of connected components.
     */
    map<Vertex, int> Tarjan();

    /** @brief Tarjan's Algorithm helper.
     *         This is a recursive function that finds strongly
     *         connected components using a DFS traversal.
     *  
     *  @param vertex The vertex to be visited next.
     *  @param ids The IDs of each vertex.
     *  @param low_link The low-link value of each vertex.
     *  @param on_stack Check if the vertex is on the stack.
     *  @param stack Stack containing the connected ancestors.
     *  @param id The current ID value.
     *  @param sccCount The current number of strongly connected
     *         components.
     */
    void TarjanHelper(Vertex vertex,
                      map<Vertex, int>& ids, 
                      map<Vertex, int>& low_link,
                      map<Vertex, bool> on_stack,
                      stack<Vertex>& stack,
                      int& id, int& sccCount);

    

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
