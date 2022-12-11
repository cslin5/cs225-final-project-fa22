#include <algorithm>
#include <stack>
#include <unordered_map>
#include <unordered_set>

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

// DFS to find connected vertices through routes

/** @todo @test
 */
bool Algorithm::RouteConnection(string route, Vertex origin,
                                Vertex destination) {
  // If the origin and destination are the same, they are obviously
  // connected.
  if (origin == destination) {
    return true;
  }

  map<Vertex, bool> visited;

  // Find out if there is an edge in between origin and destination.
  Edge edge = findEdge(route, origin, destination);
  // If there isn't, we can't move forward on route.
  if (edge == Edge()) {
    return false;
  }

  visited[origin] = true;
  // For each entry in graph:
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    // If the origin vertex hasn't been visited,
    if (!visited[it->first]) {
      RouteConnection(route, it->first, destination);
    }
  }

  return true; // ?
}

Edge Algorithm::findEdge(string route, Vertex origin, Vertex destination) {
  for (Edge edge : edges) {
    if (edge.origin == origin && edge.destination == destination &&
        edge.route == route) {
      return edge;
    }
  }

  return Edge();
}

// Dijkstra's Algorithm

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
  return solution;
}

// map<Vertex, set<Vertex>> Algorithm::Dijkstra(Vertex source) {
//   // map from vertices to whether or not it's been visited
//   unordered_map<string, bool> visited;
//   // map from vertices to it's distance from source
//   map<Edge, double> distances;
//   // shortest paths from source
//   // not using unordered cuz don't wanna define hash function
//   map<Vertex, set<Vertex>> solution;

//   for (auto vertex : vertices) {
//     // init visited as false for all vertices
//     visited.insert(pair<string, bool>(vertex.stop, false));
//   }

//   for (auto edge : edges) {
//     // init distance as INF (max double) for all vertices
//     distances.insert(pair<Edge, double>(edge, DBL_MAX));
//   }

//   Edge source_edge = Edge("", source.stop, source.stop, 0);
//   // set distance to self as 0.0
//   distances[source_edge] = 0.0;

//   std::stack<Vertex> s;
//   s.push(source);
//   for (auto v : visited) {
//     auto curr = s.top();
//     s.pop();
//     auto connected = findOutgoingEdges(curr);
//     double curr_dist = distances[source_edge];
//     for (auto edge : connected) {
//       s.push(edge.destination);
//       double edge_dist = curr_dist + edge.time;

//       // if the distance from connected edge destination to source is smaller
//       // than the currently stored value, update the distance of the edge
//       // destination in the map
//       if (edge_dist < distances[edge]) {
//         distances[edge] = edge_dist;

//         // im (calvin) assuming that when you're allowed to update distance,
//         // then it's a valid edge to add to graph
//         auto find = solution.find(edge.origin);
//         if (find != solution.end()) {
//           find->second.insert(edge.destination);
//         } else {
//           set<Vertex> connected;
//           connected.insert(edge.destination);
//           solution[edge.origin] = connected;
//         }
//       }
//     }
//     // mark curr as visited once done looking at all neighbors
//     visited[v.stop] = true;
//   }
// }
/** @test
 */
vector<Edge> Algorithm::findOutgoingEdges(Vertex vertex) {
  vector<Edge> outgoingEdges;
  for (Edge edge : edges) {
    if (edge.origin == vertex) {
      outgoingEdges.push_back(edge);
    }
  }
  return outgoingEdges;
}

/** @test
 */
vector<Edge> Algorithm::findIncomingEdges(Vertex vertex) {
  vector<Edge> incomingEdges;
  for (Edge edge : edges) {
    if (edge.destination == vertex) {
      incomingEdges.push_back(edge);
    }
  }
  return incomingEdges;
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

// Tarjan's Algorithm

/** @todo @bug Wrong output on test
 *
 *  Sources:
 *  * https://www.youtube.com/watch?v=wUgWX0nc4NY&t=398s
 *  *
 * https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 */
int Algorithm::Tarjan() {
  cout << "\nStarting Tarjan()...\n" << endl;
  map<Vertex, int> ids;
  map<Vertex, int> low_link;
  map<Vertex, bool> on_stack;
  stack<Vertex> stack;

  // Used to give each vertex an ID.
  int id = 0;
  cout << "ID starts at " << id << "." << endl;
  // Used to count number of strongly connected components (SCCs) found.
  int sccCount = 0;
  cout << "sccCount starts at " << sccCount << "." << endl;

  cout << "Initialize the vertices:" << endl;
  for (Vertex vertex : vertices) {
    // Mark the each vertex as unvisited.
    on_stack[vertex] = false;
    // Assign it an ID.
    ids[vertex] = UNVISITED;
    // Assign it a low-link value.
    low_link[vertex] = 0;

    cout << "\nvertex: " << vertex.stop << endl;
    cout << "\ton_stack: " << (on_stack[vertex] ? "true" : "false") << endl;
    cout << "\tid: " << ids[vertex] << endl;
    cout << "\tlow_link: " << low_link[vertex] << endl;
  }

  cout << "\nFor each vertex in vertices:" << endl;
  for (Vertex vertex : vertices) {
    if (ids[vertex] == UNVISITED) {
      cout << "Vertex " << vertex.stop << " is unvisited." << endl;
      TarjanHelper(vertex, ids, low_link, on_stack, stack, id, sccCount);
    }
  }

  cout << "\n\nThe number of strongly connected components is " << sccCount
       << "." << endl;
  return sccCount;
}

/** @todo @bug Wrong output on test
 */
void Algorithm::TarjanHelper(Vertex vertex, map<Vertex, int> &ids,
                             map<Vertex, int> &low_link,
                             map<Vertex, bool> on_stack, stack<Vertex> &stack,
                             int &id, int &sccCount) {
  stack.push(vertex);
  on_stack[vertex] = true;
  ids[vertex] = low_link[vertex] = id++;

  cout << "\tID:\t\t" << ids[vertex] << endl;
  cout << "\tlow_link:\t" << low_link[vertex] << endl;
  cout << "\tStack top:\t" << stack.top().stop
       << " | Stack size = " << stack.size() << endl
       << endl;

  // Visit all neighbors and min low-link value on callback.
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    Vertex destination = it->first;

    if (ids[destination] == UNVISITED) {
      cout << "\t** Recursive Tarjan..." << endl;
      TarjanHelper(destination, ids, low_link, on_stack, stack, id, sccCount);
      low_link[vertex] =
          ((low_link[vertex] < low_link[destination]) ? low_link[vertex]
                                                      : low_link[destination]);
      cout << "\tLow-link value for " << vertex.stop << " is "
           << low_link[vertex] << endl;
      cout << "\t** End Recursive Tarjan." << endl;
    } else if (on_stack[destination]) {
      low_link[vertex] =
          ((low_link[vertex] < ids[destination]) ? low_link[vertex]
                                                 : ids[destination]);
      cout << "\tLow-link value for " << vertex.stop << " is "
           << low_link[vertex] << endl;
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
    cout << "\n\tsccCount = " << sccCount << endl;
  }
}
