#pragma once

#include <string>   /* for std::string */
#include <vector>   /* for std::vector */

#include "../lib/edge.h"

using namespace std;


/** @brief A Transit object transforms a TXT file 
 *         into vectors of vertices and edges.
 * 
 *         It contains information about each vertex
 *         and edge.
 *         
 *         It is used in Algorithm to form a graph.
 */
class Transit {
public:
    /* Constructors */

    /** @brief Default constructor of Transit.
     */
    Transit() { /* Do nothing. */}

    /** @brief Parametrized constructor of Transit.
     *         Reads the data in `dataset` and transforms
     *         it into vertices and edges.
     * 
     *         It first creates all possible vertices,
     *         and then it uses those vertices to create
     *         edges.
     * 
     *  @param dataset Dataset to be parsed.
     */
    Transit(const string& dataset);


    /* Helper Functions */

    /** @brief Creates all edges given existing vertices and
     *         parsed data.
     * 
     *  @param data parsed data.
     */
    void createEdges(vector<vector<string>> data);

    /** @brief Finds vertex in vertices vector.
     * 
     *  @param stop stop ID to be searched
     *  @return index of found vertex. If not found,
     *          returns -1.
     */
    int findVertex(string stop);

    /** @brief Calculates the time in seconds between two strings
     *         representing time in the format HH:MM:SS.
     * 
     *  @param time1 first time.
     *  @param time2 second time.
     *  @return the difference between times.
     */
    double findTime(string time1, string time2);


    /* Getters */

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
     * Represents all created vertices.
     */
    vector<Vertex> vertices;
    
    /* 
     * Represents all created edges.
     */
    vector<Edge> edges;
};