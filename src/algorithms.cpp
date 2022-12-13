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
      return vertex;
    }
  }

  return Vertex();
}

// Prim's Algorithm (Deeya) (Calvin)

map<Vertex, map<Vertex, Edge>> Algorithm::Prim() {
  map<Vertex, double> shortest_time;
  map<Vertex, Edge> cheapest_edge;
  set<Vertex> unvisited;
  // initialize costs as INF/MAX and point edge to NULL, fill unvisited with all
  // vertices
  for (auto v : vertices) {
    shortest_time.insert(pair<Vertex, double>(v, DBL_MAX));
    cheapest_edge.insert(pair<Vertex, Edge>(v, Edge()));
    unvisited.insert(v);
  }

  map<Vertex, map<Vertex, Edge>> solution;

  // run until all nodes visited
  while (!unvisited.empty()) {
    // check neighboring adjacency
    for (auto edge : findOutgoingEdges(*unvisited.begin())) {
      auto find = unvisited.find(edge.destination);

      // if already visited, skip
      if (find == unvisited.end())
        continue;

      cout << edge.origin.stop << "->" << edge.destination.stop << " ("
           << edge.time << " < " << shortest_time[edge.destination] << endl;
      // if edge's time is cheaper, update shortest_time and cheapest_edge
      if (edge.time < shortest_time[edge.destination]) {
        cout << "yep, shortest" << endl;
        shortest_time[edge.destination] = edge.time;
        cheapest_edge[edge.destination] = edge;
      }
    }

    unvisited.erase(unvisited.begin());
  }
  for (auto p : cheapest_edge) {
    // if no attributed least weight edge, skip iteration
    if (p.second == Edge()) {
      continue;
    }

    auto find = solution.find(p.second.origin);
    if (find == solution.end()) {
      // insert new map if no map currently exists
      map<Vertex, Edge> tmp;
      tmp.insert(pair<Vertex, Edge>(p.second.destination, p.second));
      solution.insert(pair<Vertex, map<Vertex, Edge>>(p.second.origin, tmp));
    } else {
      // add cheap edge to vertex-edge map
      find->second.insert(pair<Vertex, Edge>(p.second.destination, p.second));
    }

    // do the same for the other vertex
    find = solution.find(p.second.destination);
    if (find == solution.end()) {
      // insert new map if no map currently exists
      map<Vertex, Edge> tmp;
      tmp.insert(pair<Vertex, Edge>(p.second.destination, p.second));
      solution.insert(pair<Vertex, map<Vertex, Edge>>(p.second.origin, tmp));
    } else {
      // add cheap edge to vertex-edge map
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

// Tarjan's Algorithm (Natalia)

void printLowLink(map<Vertex, int> low_link) {
  cout << "\nPrinting low_link:" << endl;
  for (auto &pair : low_link) {
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

  cout << "\n\nAfter initializing every node, analize every vertex if it is "
          "unvisited."
       << endl;
  for (Vertex vertex : vertices) {
    if (ids[vertex] == UNVISITED) {
      TarjanHelper(vertex, ids, low_link, on_stack, stack, sccCount);
      cout << "\t\tEnd of TarjanHelper()." << endl;
    } else {
    }
  }

  cout << "\nStates for every vertex:" << endl;
  for (Vertex vertex : vertices) {
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
  cout << "\t\t\tstack.size =\t" << stack.size() << endl;

  // Visit all neighbors and min low-link value on callback.
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    Vertex destination = it->first;

    if (ids[destination] == UNVISITED) {
      cout << "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           << endl;
      cout << "\n\t\t\t** Starting Recursive Tarjan for vertex ";

      TarjanHelper(destination, ids, low_link, on_stack, stack, sccCount);

      cout << endl;
      cout << "\t\t\t--------------------------------------------------------"
           << endl;

      low_link[vertex] =
          ((low_link[vertex] <= low_link[destination]) ? low_link[vertex]
                                                       : low_link[destination]);
      cout << low_link[vertex] << endl;
    }

    if (on_stack[destination]) {

      low_link[vertex] =
          ((low_link[vertex] <= ids[destination]) ? low_link[vertex]
                                                  : ids[destination]);
      cout << low_link[vertex] << endl;
    }
  }

  if (ids[vertex] == low_link[vertex]) {

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
  }
}
