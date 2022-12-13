#pragma once

#include <map>              /* for std::map */
#include <stack>            /* for std::stack */
#include <string>           /* for std::string */
#include <vector>           /* for std::vector */

#include "transit.h"

using namespace std;


/** @brief Algorithm provides functions to be used
 *         in an adjacency list, such as Tarjan's
 *         algorithm, Prim's algorithm, and a DFS
 *         traversal.
 */
class Algorithm {
public:
    /* Constructors*/

    /** @brief Default constructor for Algorithm.
     */
    Algorithm() { /* Do nothing. */ }

    /** @brief Parametrized constructor for algorithm.
     *         Constructs a graph with a given vector of vertices and
     *         edges.
     * 
     *  @param vertices_ vector of vertices parsed from dataset.
     *  @param edges_ vector of edges parsed from dataset.
     */
    Algorithm(vector<Vertex> vertices_, vector<Edge> edges_);


    /* Helper Functions */

    /** @brief Fills the graph with information about the edges.
     *         This will end up connecting the vertices in the graph.
     * 
     *         Creates an adjacency list.
     */
    void buildGraph();

    /** @brief Finds the vertex in vertices with the given stop ID.
     * 
     *  @param stop The stop ID to search for.
     *  @return the vertex object with the given ID.
     */
    Vertex findVertex(string stop);


    /* DFS Traversal and Helpers */

    /** @brief Route Connection returns if there is a connection between
     *         a given stop to another stop using a certain route.
     * 
     *  @param route Route ID.
     *  @param origin_stop Stop ID of origin.
     *  @param destination_stop Stop ID of destination.
     *  @return if we found a connection.
     */
    bool RouteConnection(string route, string origin_stop, string destination_stop);

    /** @brief Recursive helper function for RouteConnetion.
     *         Keeps iterating though origins, and, if origin
     *         is ever the same as destination, returns true.
     * 
     *  @param route Route ID.
     *  @param origin Vertex origin.
     *  @param destination Vertex destination.
     *  @param visited Map that checks if certain Vertex was already visited.
     *  @return if we found a connection.
     */
    bool RouteConnectionHelper(string route, Vertex origin, Vertex destination, map<Vertex, bool>& visited);

    
    /* Prim's Algorithm and Helpers */
    
    /** @brief Finds minimum spanning tree of bus stops based on
     *         time.
     * 
     *  @return Minimum spanning tree of bus stops.
     */
    map<Vertex, map<Vertex, Edge>> Prim();

    /** @brief Finds all edges leaving the passed vertex.
     * 
     *  @param vertex Vertex to be analyzed.
     *  @return all edges with origin equals to vertex.
     */
    vector<Edge> findOutgoingEdges(Vertex vertex);

    /** @brief Edge time comparison struct for priority queue.
     */
    struct CompareTime {
        /** @brief Edge time comparison struct for priority queue.
         * 
         *  @param a Edge a.
         *  @param b Edge b.
         *  @return if a has larger time than b.
         */
        constexpr bool operator()(Edge const &a, Edge const &b) const noexcept {
            return a.time > b.time;
        }
    };


    /* Tarjan's Algorithm and Helpers */

    /** @brief Tarjan's Algorithm.
     *         This is an algorithm used to find the strongly connected
     *         components of a graph.
     * 
     *  @return the low-link value of the vertices.
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
     *  @param sccCount The current number of strongly connected
     *         components.
     */
    void TarjanHelper(Vertex vertex,
                      map<Vertex, int>& ids, 
                      map<Vertex, int>& low_link,
                      map<Vertex, bool> on_stack,
                      stack<Vertex>& stack,
                      int& sccCount);


    /* Getters */

    /** @brief Getter for graph.
     * 
     *  @return graph.
     */
    map<Vertex, map<Vertex, vector<Edge>>>& getGraph();

    /** @brief Getter for vertices.
     *  
     *  @return vertices.
     */
    vector<Vertex>& getVertices();

    /** @brief Getter for edges.
     *  
     *  @return edges.
     */
    vector<Edge>& getEdges();

private:
    /* Variables */

    /* 
     * This is an weighted, directed adjacency list.
     * This constitutes the graph of stops (vertices) and routes (edges).
     */
    map<Vertex, map<Vertex, vector<Edge>>> graph;

    /* 
     * Represents all stops (vertices).
     */
    vector<Vertex> vertices;

    /* 
     * Represents all routes (edges).
     */
    vector<Edge> edges;
};
