#include <algorithm>
#include <stack>

#include "algorithms.h"

#define UNVISITED -1


// Constructors

Algorithm::Algorithm(vector<Vertex> vertices_, vector<Edge> edges_) : 
        vertices(vertices_), edges(edges_) {
    buildGraph();
}

void Algorithm::buildGraph() {
    for (Edge edge : edges) {
        graph[edge.origin][edge.destination].push_back(edge);
    }
}


// Getters

map<Vertex, map<Vertex, vector<Edge>>>& Algorithm::getGraph() {
    return graph;
}


// DFS to find connected vertices through routes (Kalika)

/** @todo @test
 */
bool Algorithm::RouteConnection(string route, string origin, string destination,  map<Vertex, bool>& visited) {
    // If the origin and destination are the same, they are obviously
    // connected.
    if (origin == destination) {
        cout << "Found destination" << endl;
        return true;
    }

    // map<Vertex, bool> visited;
    // for (Vertex v : vertices)
    //     visited[v] = false;

    Vertex start = findVertex(origin);
    Vertex end = findVertex(destination);
    // Find out if there is an edge in between origin and destination.
    Edge edge = findEdge(route, start, end);
    // // If there isn't, we can't move forward on route.
    if (edge == Edge()) {
        return false;
        cout << "Can't move foward" << endl;
    }

    visited[start] = true;
    // For each entry in graph:
    for (auto it = graph[start].begin(); it != graph[start].end(); ++it) {   
        // If the origin vertex hasn't been visited,
        cout << "enter graph iteration" << endl;
        bool has_route = false;
        string stop = "";
        for (Edge e : it -> second) { 
            if (visited.find(it->first) != visited.end() && !visited[it->first] && e.route == route) {
            cout << "not visited" << endl;
            has_route = true;
            stop = it -> first.stop;
            RouteConnection(route, it->first.stop, destination, visited);
            }
        }
        if (has_route && stop != destination) {
            return false;
            cout << "Can't move foward and not at stop" << endl;
        }
    }

    return true; // ?
}

Edge Algorithm::findEdge(string route, Vertex origin, Vertex destination) {
    for (Edge edge : graph[origin][destination]) {
        if (edge.route == route) {
            // cout << "Edge was found." << endl;
            return edge;
        }
    }
    // cout << "Edge was not found." << endl;
    return Edge();
}

Vertex Algorithm::findVertex(string stop) {
    for (Vertex vertex : vertices) {
        if (vertex.stop == stop) {
            // cout << "Vertex was found." << endl;
            return vertex;
        }    
    }

    // cout << "Vertex was not found." << endl;
    return Vertex(); 
}

// Dijkstra's Algorithm (Deeya) (Calvin)

/** @todo @test
 * 
 *  Sources:
 *  * https://favtutor.com/blogs/dijkstras-algorithm-cpp#:~:text=What%20is%20Dijkstra's%20Algorithm%3F,other%20points%20in%20the%20graph.
 *  * https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 */
map<Vertex, double> Algorithm::Dijkstra(Vertex source) {
    size_t source_idx = findVertexIndex(source);
    
    // vector<Vertex> vertices;
    // Vector to calculate the minimum interval for each vertex.
    vector<double> intervals(vertices.size(), DBL_MAX);
    // Vector to mark visited and unvisited for each vertex.
    vector<bool> visited(vertices.size(), false);

    // Source vertex interval is 0.
    intervals[source_idx] = 0;

    // Find shortest interval for all vertices.
    for (size_t i = 0; i < vertices.size(); i++) {
        // Pick the minimum interval vertex from the set of vertices
        // not yet processed. 'min' is always equal to source in the
        // first iteration.
        size_t vertex_idx = minInterval(intervals, visited); // what does this do?
        Vertex vertex = vertices[i];
        
        // Mark the picked vertex as processed.
        visited[vertex_idx] = true;

        // Update interval value of the adjacent vertices of the
        // picked vertex.
        for (size_t j = 0; j < vertices.size(); i++) {
            // Update interval[vertex_idx] only if it wasn't visited,
            // there is an edge from vertices[vertex_idx] to vertices[j],
            // and total interval of path from source to vertices[j]
            // through vertices[vertex_idx] is smaller than current
            // value of interval[vertex_idx].
            for (Edge edge : graph[vertex][vertices[j]]) {
                if ((!visited[j]) && (intervals[vertex_idx] != DBL_MAX) &&
                    (intervals[vertex_idx] + edge.time < intervals[j])) {
                        intervals[j] = intervals[vertex_idx] + edge.time;
                    }
            }
        }
    }

    return map<Vertex, double>(); // ?
}

/** @test
 */
int Algorithm::minInterval(vector<double> intervals, vector<bool> visited) {
    double min = DBL_MAX;
    int min_index;

    for (size_t i = 0; i < vertices.size(); i++) {
        if (!visited[i] && intervals[i] <= min) {
            min = intervals[i];
            min_index = i;
        }
    }

    return min_index;
}

/** @test
 */
int Algorithm::findVertexIndex(Vertex vertex) {
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertex == vertices[i]) {
            return i;
        }
    }
    return -1;
}


// Tarjan's Algorithm (Natalia)

void printLowLink(map<Vertex, int> low_link) {
    cout << "\nPrinting low_link:" << endl;
    for (auto& pair : low_link) {
        cout << (pair.first).stop << ": " << pair.second << endl;
    }
}

/** Sources:
 *  * https://www.youtube.com/watch?v=wUgWX0nc4NY&t=398s
 *  * https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 */
map<Vertex, int> Algorithm::Tarjan() {
    cout << "\n~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Starting Tarjan()...\n" << endl;
    
    map<Vertex, int>  ids;
    map<Vertex, int>  low_link;
    map<Vertex, bool> on_stack;
    stack<Vertex>     stack;

    // Used to count number of strongly connected components (SCCs) found.
    int sccCount = 0;

    cout << "Initialize all the vertices to on_stack=false, ids=-1, low_link=0." << endl;
    for (Vertex vertex : vertices) {
        // Mark the each vertex as unvisited.
        on_stack[vertex] = false;
        // Assign it an ID.
        ids[vertex] = UNVISITED;
        // Assign it a low-link value.
        low_link[vertex] = 0;
    }

    cout << "\n\nAfter initializing every node, analize every vertex if it is unvisited." << endl;
    for (Vertex vertex : vertices) {
        cout << "\n\tVertex = " << vertex.stop << endl;
        if (ids[vertex] == UNVISITED) {
            cout << "\t\t" << vertex.stop << " is unvisited" << endl;
            cout << "\t\tCalling TarjanHelper() on " << vertex.stop << endl;
            TarjanHelper(vertex, ids, low_link, on_stack, stack, sccCount);
            cout << "\t\tEnd of TarjanHelper()." << endl;
        } else {
            cout << "\t\t" << vertex.stop << " is visited" << endl;
        }
    }

    cout << "\nStates for every vertex:" << endl;
    for (Vertex vertex : vertices) {
        cout << "\tVertex = " << vertex.stop << endl;
        cout << "\t\tids =\t\t" << ids[vertex] << endl;
        cout << "\t\tlow_link =\t" << low_link[vertex] << endl;
        cout << "\t\ton_stack =\t" << on_stack[vertex] << endl;
    }

    printLowLink(low_link);
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

    cout << "\t\t\tids =\t\t" << ids[vertex] << endl;
    cout << "\t\t\tlow_link =\t" << low_link[vertex] << endl;
    cout << "\t\t\ton_stack =\t" << on_stack[vertex] << endl;
    cout << "\t\t\tstack.top =\t" << stack.top().stop << endl;
    cout << "\t\t\tstack.size =\t" << stack.size() << endl;
    
    // Visit all neighbors and min low-link value on callback.
    for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
        Vertex destination = it->first;
        cout << "\n\t\t\tdestination =\t" << destination.stop << endl;

        if (ids[destination] == UNVISITED) {
            cout << "\t\t\t" << destination.stop << " is unvisited" << endl;
            cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n\t\t\t** Starting Recursive Tarjan for vertex " << destination.stop << endl;

            TarjanHelper(destination, ids, low_link, on_stack, stack, sccCount);

            cout << "\n\t\t\t** End Recursive Tarjan for vertex " << destination.stop<< endl;
            cout << "\t\t\t--------------------------------------------------------" << endl;
            cout << "\t\t\tCalling back vertex " << vertex.stop << endl;
            
            low_link[vertex] = ((low_link[vertex] <= low_link[destination]) ? low_link[vertex] : low_link[destination]);
            cout << "\t\t\tUpdating low-link value for " << vertex.stop << " to " << low_link[vertex] << endl;
        }

        if (on_stack[destination]) {
            cout << "\t\t\t" << destination.stop << " has been visited" << endl;

            low_link[vertex] = ((low_link[vertex] <= ids[destination]) ? low_link[vertex] : ids[destination]);
            cout << "\t\t\tUpdating low-link value for " << vertex.stop << " to " << low_link[vertex] << endl;
        }
    }


    if (ids[vertex] == low_link[vertex]) {
        cout << "\n\t\t\tids = low_link for vertex " << vertex.stop << endl;
        
        while (!stack.empty()) {
            Vertex tmp = stack.top();
            stack.pop();

            on_stack[tmp] = false;
            low_link[tmp] = ids[vertex];

            if (tmp == vertex)
                break;
        }

        sccCount++;
        cout << "\t\t\t-> increment sccCount to " << sccCount << endl;
    } else {
        cout << "\n\t\t\tids != low_link for vertex " << vertex.stop << endl;
    }
}
