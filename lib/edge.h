#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "vertex.h"

using namespace std;


/** @brief Edges identify routes.
 *         Each edge has the route identification, an origin
 *         and a destination, and the time it takes to go from
 *         origin to destination.
 */
struct Edge {
    /* Variables */
    
    /*
     * Represents the route identification.
     */
    string route;
    
    /*
     * Represents the original stop.
     */
    Vertex origin;
    
    /*
     * Represents the destination stop.
     */
    Vertex destination;
    
    /*
     * Represents the time it takes to go from origin to
     * destination. Time is the weight of the edge.
     */
    double time;


    /* Constructors */

    /** @brief Default constructor of Edge.
     *         Initializes route to empty string, origin
     *         and destination to empty vertices, and
     *         time to zero. 
     */
    Edge() : route(""), origin(Vertex()), destination(Vertex()),
            time(0.0) { /* Do nothing. */ }

    /** @brief Parametrized constructor of Vertex.
     *         Creates a stop.
     *  
     *  @param route_ new route identification.
     *  @param origin_ vertex from where the route comes from.
     *  @param destination_ vertex to where the route goes.
     *  @param time_ time it takes to go from origin to destination.
     *         It is the weight of the edge.
     */
    Edge(string route_, Vertex origin_, Vertex destination_, double time_) :
            route(route_), origin(origin_), destination(destination_),
            time(time_) { /* Do nothing. */}


    /* Overloading operators */

    /** @brief Overloading comparison operator '=='.
     *  
     *  @param other Edge to be compared to.
     *  @return if edges have equal routes, origin,
     *          detination, and time.
     */
    bool operator==(const Edge& other) const {
        return (route == other.route) && (origin == other.origin) &&
                (destination == other.destination) && (time == other.time);
    }

    /** @brief Overloading comparison operator '=='.
     *  
     *  @param other Edge to be compared to.
     *  @return if this edge has smaller time than
     *          other's time.
     */
    bool operator<(const Edge& other) const {
        return (time < other.time);
    }

    /** @brief Overloading comparison operator '<='.
     *  
     *  @param other Edge to be compared to.
     *  @return if this edge has smaller or equal time
     *          to other's time.
     */
    bool operator<=(const Edge& other) const {
        return (time <= other.time);
    }
};
