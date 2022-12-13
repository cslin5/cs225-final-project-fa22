#pragma once

#include <iostream> /* for std::cout, std::endl */
#include <string>   /* for std::string */
#include <vector>   /* for std::vector */

using namespace std;


/** @brief A Vertex represents a bus stop.
 *         Each vertex has a stop ID in string.
 */
struct Vertex {
    /* Variables */
    
    /*
     * Bus stop identification.
     */
    string stop;


    /* Constructors */

    /** @brief Default constructor of Vertex.
     */
    Vertex() { /* Do nothing. */ }

    /** @brief Parametrized constructor of Vertex.
     *         Creates a vertex with given stop ID.
     *  
     *  @param stop_ Stop ID of new Vertex.
     */
    Vertex(string stop_) : stop(stop_) { /* Do nothing. */ }

    /** @brief Copy constructor of Vertex.
     *  
     *  @param other Vertex to be copied.
     */
    Vertex(const Vertex& other) {
        stop = other.stop;
    }


    /* Operator Overloading */

    /** @brief Overloading comparison operator '=='.
     *  
     *  @param other Vertex to be compared to.
     *  @return if vertices have equal stop IDs.
     */
    bool operator==(const Vertex& other) const {
        return (stop == other.stop);
    }

    /** @brief Overloading comparison operator '=='.
     *  
     *  @param other Vertex to be compared to.
     *  @return if vertices have equal stop IDs.
     */
    bool operator<(const Vertex& other) const {
        return (stop < other.stop);
    }

};
