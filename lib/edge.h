#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "vertex.h"

using namespace std;


/** @brief Edges identify routes. Each edge has the route identification,
 *         an origin and a destination, and the time it takes to go from
 *         origin to destination.
 * 
 *         There is only one edge from a specific origin to a specific
 *         destination.
 */
struct Edge {
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
     * Represents the time it takes to go from origin to destination.
     Time is the weight of the edge.
     */
    double time;


    /** @brief Default constructor of Edge.
     */
    Edge() { /* Do nothing. */ }

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
            route(route_), origin(origin_), destination(destination_), time(time_) {
        cout << "-> Created edge with route = " << route << ", origin = " << origin.stop
                << ", destination = " << destination.stop << ", and time = " << time << "s." << endl;
    }


    /* Overloading operators */

    bool operator==(const Edge& other) const {
        return (route == other.route) && (origin == other.origin) &&
                (destination == other.destination) && (time == other.time);
    }

    bool operator<(const Edge& other) const {
        return (time < other.time);
    }

    bool operator<=(const Edge& other) const {
        return (time <= other.time);
    }
};
