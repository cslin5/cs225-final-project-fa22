#include "algo.hpp"

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

vector<vector<vector<Edge>>> graph;

void build_graph(vector<Vertex> all_verticies, vector<Edge> all_edges){
// pseudocode instructions

// resize the graph vector to 
for(int i = 0; i < all_verticies.size(); i++) {
  vector<vector<Edge>> outer_vec = vector<vector<Edge>>();
  for(int j = 0; j < all_verticies.size(); j++) {
    vector<Edge> inner_vec = vector<Edge>();
    inner_vec.push_back(Edge());
    outer_vec.push_back(inner_vec);
    }
  graph.push_back(outer_vec);
}

// for each edge, find the vertex and set their distance
  for(int i = 0; i < all_edges.size(); i++) {
    Vertex start_ = all_edges[i].start;
    Vertex destination_ = all_edges[i].end;

    int start_index = find_index_in_vector(all_verticies, start_);
    int destination_index = find_index_in_vector(all_verticies, destination_);

    graph[start_index][destination_index].push_back(all_edges[i]);
    graph[destination_index][start_index].push_back(all_edges[i]);
  }
}

int find_index_in_vector(vector<Vertex> all_verticies, Vertex v) {
  //user iterator to locate element
  auto location = find(v.begin(), v.end(), K);
  // If element doesn't exist return -1
  if (location == v.end()) {
    return -1;
  }
  return location - v.begin();
}
