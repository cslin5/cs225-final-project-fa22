#include <algorithm>
#include <iostream>
#include <stack>

#include "algorithms.h"

#define UNVISITED -1

using std::cout;
using std::endl;
using std::pair;
using std::unordered_map;
using std::unordered_set;
// Constructors

Algorithm::Algorithm(vector<Vertex> vertices_, vector<Edge> edges_)
    : vertices(vertices_), edges(edges_) {
  buildGraph();
}

void Algorithm::buildGraph() {
  for (Edge edge : edges) {
    graph[edge.origin][edge.destination].push_back(edge);
  }
}

// Getters

map<Vertex, map<Vertex, vector<Edge>>> &Algorithm::getGraph() { return graph; }

// DFS to find connected vertices through routes (Kalika) (Natalia)

bool Algorithm::RouteConnection(string route, string origin_stop,
                                string destination_stop) {
  // If the origin is the same as destination, exit the code.
  if (origin_stop == destination_stop) {
    cout << "Destination was found!" << endl;
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
bool Algorithm::RouteConnectionHelper(string route, Vertex origin,
                                      Vertex destination,
                                      map<Vertex, bool> &visited) {
  cout << "\nRouteConnection for " << route << " from " << origin.stop << " to "
       << destination.stop << endl;

  // If the origin and destination are the same, they are obviously connected.
  if (origin.stop == destination.stop) {
    cout << "Destination was found!" << endl;
    return true;
  }

  // Mark the origin as true so we don't visit it again.
  visited[origin] = true;

  // For each origin in graph, iterate through the destinations:
  cout << "Entering graph iteration..." << endl;
  for (auto it = graph[origin].begin(); it != graph[origin].end(); ++it) {
    // For each edge coming out from origin,
    for (Edge edge : it->second) {
      // If the edge has the same route,
      if (!visited[it->first] && edge.route == route) {
        cout << "Edge was found between " << origin.stop << " and "
             << it->first.stop << endl;
        // Return the RoutConnection recursive function's result.
        if (RouteConnectionHelper(route, it->first, destination, visited) ==
            true) {
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
 *  *
 * https://favtutor.com/blogs/dijkstras-algorithm-cpp#:~:text=What%20is%20Dijkstra's%20Algorithm%3F,other%20points%20in%20the%20graph.
 *  *
 * https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 */
vector<Edge> Algorithm::Dijkstra(Vertex source) {
  size_t source_idx = findVertexIndex(source);

  // vector<Vertex> vertices;
  // Vector to calculate the minimum interval for each vertex.
  vector<double> intervals(vertices.size(), DBL_MAX);
  // Vector to mark visited and unvisited for each vertex.
  vector<bool> shortest_interval(vertices.size(), false);
  // Solution vector of edges
  vector<Edge> solution;

  // Source vertex interval is 0.
  intervals[source_idx] = 0;

  // Find shortest interval for all vertices.
  for (size_t i = 0; i < vertices.size(); i++) {
    // Pick the minimum interval vertex from the set of vertices
    // not yet processed. 'min' is always equal to source in the
    // first iteration.
    size_t vertex_idx =
        minInterval(intervals, shortest_interval); // what does this do?
    Vertex vertex = vertices[i];

    // Mark the picked vertex as processed.
    shortest_interval[vertex_idx] = true;

    // Update interval value of the adjacent vertices of the
    // picked vertex.
    for (size_t j = 0; j < vertices.size(); j++) {
      // Update interval[vertex_idx] only if it wasn't visited,
      // there is an edge from vertices[vertex_idx] to vertices[j],
      // and total interval of path from source to vertices[j]
      // through vertices[vertex_idx] is smaller than current
      // value of interval[vertex_idx].

      cout << __LINE__ << ": " << j << endl;
      for (Edge edge : graph[vertex][vertices[j]]) {
        cout << edge.origin.stop << " : " << edge.destination.stop << endl;
        if ((!shortest_interval[j]) && (intervals[vertex_idx] != DBL_MAX) &&
            (intervals[vertex_idx] + edge.time < intervals[j])) {
          intervals[j] = intervals[vertex_idx] + edge.time;
          solution.push_back(edge);
        }
      }
    }
  }
  return vector<Edge>();
}

map<Vertex, map<Vertex, Edge>> Algorithm::Prim() {
  map<Vertex, double> shortest_time;
  map<Vertex, Edge *> cheapest_edge;
  set<Vertex> unvisited;
  // initialize costs as INF/MAX and point edge to NULL, fill unvisited with all
  // vertices
  for (auto v : vertices) {
    shortest_time.insert(pair<Vertex, double>(v, DBL_MAX));
    cheapest_edge.insert(pair<Vertex, Edge *>(v, NULL));
    unvisited.insert(v);
  }

  map<Vertex, map<Vertex, Edge>> solution;

  while (!unvisited.empty()) {
    auto curr = unvisited.begin();
    unvisited.erase(unvisited.begin());
    for (auto edge : findOutgoingEdges(*curr)) {
      auto find = unvisited.find(edge.destination);

      // if already visited, skip
      if (find == unvisited.end())
        continue;

      // if edge's time is cheaper, update shortest_time and cheapest_edge
      if (edge.time < shortest_time[edge.destination]) {
        shortest_time[edge.destination] = edge.time;
        cheapest_edge[edge.destination] = &edge;
      }
    }
  }

  for (auto p : cheapest_edge) {
    auto find = solution.find(p.first);

    if (find == solution.end()) {
      // insert new map
      map<Vertex, Edge> tmp;
      tmp.insert(pair<Vertex, Edge>(p.second->origin, *(p.second)));
      solution.insert(pair<Vertex, map<Vertex, Edge>>(p.second->origin, tmp));
    } else {
      // add cheap edge to vertex
      find->second.insert(pair<Vertex, Edge>(p.second->origin, *(p.second)));
    }
  }
  return solution;
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
  for (auto &pair : low_link) {
    cout << (pair.first).stop << ": " << pair.second << endl;
  }
}

/** Sources:
 *  * https://www.youtube.com/watch?v=wUgWX0nc4NY&t=398s
 *  *
 * https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 */
map<Vertex, int> Algorithm::Tarjan() {
  cout << "\n~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "Starting Tarjan()...\n" << endl;

  map<Vertex, int> ids;
  map<Vertex, int> low_link;
  map<Vertex, bool> on_stack;
  stack<Vertex> stack;

  // Used to count number of strongly connected components (SCCs) found.
  int sccCount = 0;

  cout << "Initialize all the vertices to on_stack=false, ids=-1, low_link=0."
       << endl;
  for (Vertex vertex : vertices) {
    // Mark the each vertex as unvisited.
    on_stack[vertex] = false;
    // Assign it an ID.
    ids[vertex] = UNVISITED;
    // Assign it a low-link value.
    low_link[vertex] = 0;
  }
}

cout << "\n\nAfter initializing every node, analize every vertex if it is "
        "unvisited."
     << endl;
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

void Algorithm::TarjanHelper(Vertex vertex, map<Vertex, int> &ids,
                             map<Vertex, int> &low_link,
                             map<Vertex, bool> on_stack, stack<Vertex> &stack,
                             int &sccCount) {
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
      cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           << endl;
      cout << "\n\t\t\t** Starting Recursive Tarjan for vertex "
           << destination.stop << endl;

      TarjanHelper(destination, ids, low_link, on_stack, stack, sccCount);

      cout << "\n\t\t\t** End Recursive Tarjan for vertex " << destination.stop
           << endl;
      cout << "\t\t\t--------------------------------------------------------"
           << endl;
      cout << "\t\t\tCalling back vertex " << vertex.stop << endl;

      low_link[vertex] =
          ((low_link[vertex] <= low_link[destination]) ? low_link[vertex]
                                                       : low_link[destination]);
      cout << "\t\t\tUpdating low-link value for " << vertex.stop << " to "
           << low_link[vertex] << endl;
    }

    if (on_stack[destination]) {
      cout << "\t\t\t" << destination.stop << " has been visited" << endl;

      low_link[vertex] =
          ((low_link[vertex] <= ids[destination]) ? low_link[vertex]
                                                  : ids[destination]);
      cout << "\t\t\tUpdating low-link value for " << vertex.stop << " to "
           << low_link[vertex] << endl;
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
