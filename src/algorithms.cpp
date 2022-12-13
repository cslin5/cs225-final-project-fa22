#include <algorithm>        /* for algorithms' functions */
#include <bits/stdc++.h>    /* for DBL_MAX */
#include <iostream>         /* for std::cout, std::ednl */
#include <set>              /* for std::set */

#include "algorithms.h"

#define UNVISITED -1


Algorithm::Algorithm(vector<Vertex> vertices_, vector<Edge> edges_) : 
        vertices(vertices_), edges(edges_) {
    // Calls the build graph function to create adjacency list.
    buildGraph();
}

void Algorithm::buildGraph() {
    // Pushes all the information into graph as an adjacency list.
    for (Edge edge : edges) {
        graph[edge.origin][edge.destination].push_back(edge);
    }
}

bool Algorithm::RouteConnection(string route, string origin_stop, string destination_stop) {
     // If the origin is the same as destination, exit the code.
    if (origin_stop == destination_stop) {
        // Destination was found.
        return true;
    }

    // Else, create a map of vertices to bool to keep track of visited nodes.
    map<Vertex, bool> visited;
    // Mark all of them as unvisited.
    for (Vertex vertex : vertices) {
        visited[vertex] = false;
    }

    // Find corresponding vertex to origin and destination stops
    Vertex origin = findVertex(origin_stop);
    Vertex destination = findVertex(destination_stop);

    // Call the recursive RouteConnection function.
    return RouteConnectionHelper(route, origin, destination, visited);
}

bool Algorithm::RouteConnectionHelper(string route, Vertex origin, Vertex destination,  map<Vertex, bool>& visited) {
    // If the origin and destination are the same, they are obviously connected.
    if (origin.stop == destination.stop) {
        // Destination was found.
        return true;
    }

    // Mark the origin as true so we don't visit it again.
    visited[origin] = true;
    
    // For each origin in graph, iterate through the destinations:
    for (auto it = graph[origin].begin(); it != graph[origin].end(); ++it) {
        // For each edge coming out from origin,
        for (Edge edge : it->second) {
            // If the edge has the same route,
            if (!visited[it->first] && edge.route == route) {
                // Return the RoutConnection recursive function's result.
                if (RouteConnectionHelper(route, it->first, destination, visited) == true) {
                    return true;
                }
            }
        }
    }

    // Else, return false: We haven't found the connection.
    return false;
}

Vertex Algorithm::findVertex(string stop) {
    for (Vertex vertex : vertices) {
        if (vertex.stop == stop) {
            // If vertex is found:
            return vertex;
        }    
    }

    // If vertex wasn't found:
    return Vertex(); 
}

map<Vertex, map<Vertex, Edge>> Algorithm::Prim() {
    map<Vertex, double> shortest_time;
    map<Vertex, Edge> cheapest_edge;
    set<Vertex> unvisited;
  
    // Initialize costs as INF/MAX and point edge to NULL,
    // fill unvisited with all vertices.
    for (auto vertex : vertices) {
        shortest_time.insert(pair<Vertex, double>(vertex, DBL_MAX));
        cheapest_edge.insert(pair<Vertex, Edge>(vertex, Edge()));
        unvisited.insert(vertex);
    }

    map<Vertex, map<Vertex, Edge>> solution;

    // Run until all nodes visited.
    while (!unvisited.empty()) {
        // Check neighboring adjacency.
        for (auto edge : findOutgoingEdges(*unvisited.begin())) {
            auto find = unvisited.find(edge.destination);

            // If already visited, skip.
            if (find == unvisited.end())
                continue;
      
            // If edge's time is cheaper, update shortest_time and
            // cheapest_edge.
            if (edge.time < shortest_time[edge.destination]) {
                shortest_time[edge.destination] = edge.time;
                cheapest_edge[edge.destination] = edge;
            }
        }

        unvisited.erase(unvisited.begin());
    }

    for (auto p : cheapest_edge) {
        // If no attributed least weight edge, skip iteration.
        if (p.second == Edge()) {
            continue;
        }

        auto find = solution.find(p.second.origin);
        if (find == solution.end()) {
            // Insert new map if no map currently exists.
            map<Vertex, Edge> tmp;
            tmp.insert(pair<Vertex, Edge>(p.second.destination, p.second));
            solution.insert(pair<Vertex, map<Vertex, Edge>>(p.second.origin, tmp));
        } else {
            // Add cheap edge to vertex-edge map.
            find->second.insert(pair<Vertex, Edge>(p.second.destination, p.second));
        }

        // Do the same for the other vertex.
        find = solution.find(p.second.destination);
        if (find == solution.end()) {
            // Insert new map if no map currently exists
            map<Vertex, Edge> tmp;
            tmp.insert(pair<Vertex, Edge>(p.second.destination, p.second));
            solution.insert(pair<Vertex, map<Vertex, Edge>>(p.second.origin, tmp));
        } else {
            // Add cheap edge to vertex-edge map.
            find->second.insert(pair<Vertex, Edge>(p.second.destination, p.second));
        }
    }

    return solution;
}

vector<Edge> Algorithm::findOutgoingEdges(Vertex vertex) {
    vector<Edge> outgoingEdges;

    for (Edge edge : edges) {
        if (edge.origin == vertex) {
            outgoingEdges.push_back(edge);
        }
    }
    
    return outgoingEdges;
}


map<Vertex, int> Algorithm::Tarjan() {
    // Store discovery vertices with ids.
    map<Vertex, int>  ids;
    // Store low-link values.
    map<Vertex, int>  low_link;
    // Store if vertex is on the stack.
    map<Vertex, bool> on_stack;
    // Stack to push vertices on.
    stack<Vertex>     stack;

    // Used to count number of strongly connected components (SCCs) found.
    int sccCount = 0;

    // Initialize all vertices to on_stack = false, ids = -1, low_link = 0.
    for (Vertex vertex : vertices) {
        // Mark the each vertex as unvisited.
        on_stack[vertex] = false;
        // Assign it an ID.
        ids[vertex] = UNVISITED;
        // Assign it a low-link value.
        low_link[vertex] = 0;
    }

    // After initializing every node, analize every vertex if it is unvisited.
    for (Vertex vertex : vertices) {
        // If vertex is unvisited:
        if (ids[vertex] == UNVISITED) {
            // Call Tarjan helper.
            TarjanHelper(vertex, ids, low_link, on_stack, stack, sccCount);
        }
    }

    return low_link;
}

void Algorithm::TarjanHelper(Vertex vertex,
                             map<Vertex, int>& ids,
                             map<Vertex, int>& low_link,
                             map<Vertex, bool> on_stack,
                             stack<Vertex>& stack,
                             int& sccCount) {
    static int id = 0;
    stack.push(vertex);
    on_stack[vertex] = true;
    ids[vertex] = low_link[vertex] = id++;
    
    // Visit all neighbors and min low-link value on callback.
    for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
        Vertex destination = it->first;

        // If destination is unvisited:
        if (ids[destination] == UNVISITED) {
            // Run recursive Tarjan helper again.
            TarjanHelper(destination, ids, low_link, on_stack, stack, sccCount);
            // Callback vertex and correct it's low-link value.
            low_link[vertex] = ((low_link[vertex] <= low_link[destination]) ? low_link[vertex] : low_link[destination]);
        }

        // If destination is on the stack:
        if (on_stack[destination]) {
            // Correct it's low-link value.
            low_link[vertex] = ((low_link[vertex] <= ids[destination]) ? low_link[vertex] : ids[destination]);
        }
    }

    // If the vertex has ID equal to low-link value:
    if (ids[vertex] == low_link[vertex]) {
        // Pop items from stack until it reaches vertex.
        while (!stack.empty()) {
            Vertex tmp = stack.top();
            stack.pop();

            on_stack[tmp] = false;
            low_link[tmp] = ids[vertex];

            if (tmp == vertex)
                break;
        }

        // Increment the number of strongly-connected components.
        sccCount++;
    }
}

map<Vertex, map<Vertex, vector<Edge>>>& Algorithm::getGraph() {
    return graph;
}

vector<Vertex>& Algorithm::getVertices() {
    return vertices;
}

vector<Edge>& Algorithm::getEdges() {
    return edges;
}
