#include "algo.hpp"
#include <algorithm>

Algo::Algo(
    vector<vector<int>> g) {
  // assign the graph
  // null check
  if(g == NULL) {
    // decide what to do?
    graph = g;
  }
  graph = g;
}

// need to write this out
void Algo::DijSolve(Vertex v){
    // pseudocode instructions
    for each (Vertex v : G) {
      d[v] = +inf
      p[v] = NULL
      d[s] = 0
      PriorityQueue Q // min distance, defined by d[v]
      Q.buildHeap(G.vertices())
      Graph T // "labeled set"
      repeat n times:
      Vertex u = Q.removeMin()
      T.add(u)
      foreach (Vertex v : neighbors of u not in T):
        if cost(u, v) + d[u] < d[v] {
          d[v] = cost(u, v) + d[u]
                  p[v] = u
        }
    }
}



// presuming bus data is smth like this, so subject to change

/// @brief sets up the data for all vertices and all edges vectors -- used in the graph initialization 
// and other methods 
void Algo::translate_data(vector<Bus> buses) {
  for (Bus b : buses) {
    // vertex vector?
    vector<string> stops = b.stops;
    vector<double> times = b.times;
    /// how is the data like time being saved? route name? etc

    for (size_t index = 0; index < stops.size() - 1; index++) {
      // vertex 1 and 2
      Vertex v1(stops[index]);
      v1.addRoute(b.route);
      Vertex v2(stops[index + 1]);
      v2.addRoute(b.route);
      // don't wanna readd vertices
      if (find(all_vertices.begin(), all_vertices.end(), v1) == all_vertices.end()) {
        all_vertices.push_back(v1);
      }
      if (find(all_vertices.begin(), all_vertices.end(), v2) == all_vertices.end()) {
        all_vertices.push_back(v2);
      }

      Edge edge(times[index], b.route, v1, v2);
      all_edges.push_back(edge);
    }
  }
}

/// @brief basically for each start vertex, we get a map of its end vertex and the edges 
// that exist between these two points

void Algo::build_graph() {
  for (Edge e : all_edges) {
    graph[e.start][e.end].push_back(e);
  }
}

bool Algo::DFS_connected_on_route(string route_, string start_, string end_) {
  // found end
  if (start_ == end_) return true;

  map<Vertex, bool> visited;
  Vertex v_start = find_vertex(start_);
  Vertex v_end = find_vertex(end_);
  Edge edge = find_edge(route_, start_, end_);

  // can't move forward on route
  if (edge == Edge()) return false;

  visited[v_start] = true;
  // note, unsure about iterator notation
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    if (!visited(it -> first)) {
      DFS_connected_on_route(route_, *it.stop, end_);
    }
  }
}

// better way to translate stop name to vertex?
Vertex find_vertex(string stop_){
  for (Vertex v : all_vertices) {
    if (v.stop == stop_)
      return v;
  }
  return Vertex();
}

Edge find_Edge(string route_, Vertex start_, Vertex end_){
  for (Edge e : graph[start_][end_]) {
    if (e.route == route_)
      return e;
  }
  return Edge();
}
// vector<vector<vector<Edge>>> graph;

// void build_graph(vector<Vertex> all_vertices, vector<Edge> all_edges){
// // pseudocode instructions

// // resize the graph vector to 
// for(int i = 0; i < all_verticies.size(); i++) {
//   vector<vector<Edge>> outer_vec = vector<vector<Edge>>();
//   for(int j = 0; j < all_verticies.size(); j++) {
//     vector<Edge> inner_vec = vector<Edge>();
//     inner_vec.push_back(Edge());
//     outer_vec.push_back(inner_vec);
//     }
//   graph.push_back(outer_vec);
// }

// // for each edge, find the vertex and set their distance
//   for(int i = 0; i < all_edges.size(); i++) {
//     Vertex start_ = all_edges[i].start;
//     Vertex destination_ = all_edges[i].end;

//     int start_index = find_index_in_vector(all_verticies, start_);
//     int destination_index = find_index_in_vector(all_verticies, destination_);

//     graph[start_index][destination_index].push_back(all_edges[i]);
//     graph[destination_index][start_index].push_back(all_edges[i]);
//   }
// }

// int find_index_in_vector(vector<Vertex> all_verticies, Vertex v) {
//   //user iterator to locate element
//   auto location = find(v.begin(), v.end(), K);
//   // If element doesn't exist return -1
//   if (location == v.end()) {
//     return -1;
//   }
//   return location - v.begin();
// }


