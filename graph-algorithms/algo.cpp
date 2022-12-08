#include "algo.hpp"
#include <algorithm>

// 



// change comments
void Algo::TarjanMain(Vertex v, map<Vertex, Vertex>& disc, map<Vertex, Vertex>& low,
                    stack<Vertex>& s, map<Vertex, bool>& on_stack) {   
 
    // Initialize discovery time and low value
    s.push(v);
    stackMember[v] = true;
    disc[v] = v;
    low[v] = v;

    // Go through all vertices adjacent to this
    for (auto it = graph[v].begin(); it != graph[v].end(); ++it) {
        int v2 = it -> first; 
 
        // If v is not visited yet, then recur for it
        if (disc[v2] == Vertex()) {
            SCCUtil(v2, disc, low, s, on_stack);
 
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 (per above discussion on Disc and Low
            // value)
            int index1 = find_index_ind(v);
            int index2 = find_index_ind(v2);
            if (index2 > index1) low[v] = v2;
            else
            low[v] = v;
        }
 
        // Update low value of 'u' only of 'v' is still in
        // stack (i.e. it's a back edge, not cross edge).
        // Case 2 (per above discussion on Disc and Low
        // value)
        else if (on_stack[v] == true)
            int index1 = find_index_ind(v);
            int index2 = find_index_ind(v2);
            if (index2 > index1) low[v] = v2;
            else
            low[v] = v;
    }
 
    // head node found, pop the stack and print an SCC
    Vertex v3(); // To store stack extracted vertices
    if (low[v] == disc[v]) {
        while (s.top() != v) {
            v3 = s.top();
            on_stack[v3] = false;
            s.pop();
        }
        v3 = s.top();
        on_stack[v3] = false;
        s.pop();
    }
}
 
void Algo::TarjanDFS() {
  map <Vertex, Vertex> disc;
  map <Vertex, Vertex> low_val;
  map <Vertex, bool> on_stack;
  stack<Vertex> s;
  for (Vertex v: all_vertices) {
    disc[v] = Vertex();
    low[v] = Vertex();
    on_stack[v] = false;
  }
  for (Vertex v : all_vertices)
      if (disc[v] == false)
          TarjanMain(v, disc, low, s, on_stack);
}





// need to write this out
void Algo::DijSolve(Vertex s){
  // use func to find index location of s
  int s_loc = find_vertex_ind(s);
  vector<double> dist = vector<double>();
  vector<bool> sptSet = vector<bool>();
  
  // start of the algorithim by pushing back "infinite" (largest double) values to dist vector
  // this ensures that all actual values will be considered minimums when compared to these
  // start of the algorithim by pushing back false values to dist vector
  // basically meaning that you are setting all verticies to NOT be part of the path at the start
  for (int i = 0; i < all_verticies.size(); i++){
      dist.push_back(DOUBLE_MAX);
      sptSet.push_back(false);
  }

  // self to self distance MUST be 0
  dist[s_loc] = 0.0;

  // find shortest path for all vertices
  // size is all but self
  for (int count = 0; count < all_verticies.size() - 1; count++) {
      int min_dist_vertex_ind = minDistance(dist, sptSet);

      // Mark the picked vertex as processed
      sptSet[min_dist_vertex_ind] = true;
      for (int v = 0; v < all_verticies.size(); v++){
          if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
            dist[v] = dist[u] + graph[u][v];
          }
      }

  // print the constructed distance array
}    
    // // pseudocode instructions
    // for (Vertex v : all_vertices) {
    //   d[v] = DOUBLE_MAX;
    //   p[v] = NULL;
    //   d[s] = 0
    //   PriorityQueue Q // min distance, defined by d[v]
    //   Q.buildHeap(G.vertices())
    //   Graph T // "labeled set"
    //   repeat n times:
    //   Vertex u = Q.removeMin()
    //   T.add(u)
    //   foreach (Vertex v : neighbors of u not in T):
    //     if cost(u, v) + d[u] < d[v] {
    //       d[v] = cost(u, v) + d[u]
    //               p[v] = u
    //     }
    // }
}

// cost function to check distance
int cost(int dist[], bool sptSet[])
{   // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
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
      // don't wanna read vertices
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

Edge find_edge(string route_, Vertex start_, Vertex end_){
  for (Edge e : graph[start_][end_]) {
    if (e.route == route_)
      return e;
  }
  return Edge();
}

int find_vertex_ind(Vertex v){
  //user iterator to locate element
  auto location = find(all_verticies.begin(), all_verticies.end(), v);
  // If element doesn't exist return -1
  if (location == all_verticies.end()) {
    return -1;
  }
  return location - all_verticies.begin();
}

int minDistance(bleh){

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


// Algo::Algo(
//     vector<vector<int>> g) {
//   // assign the graph
//   // null check
//   if(g == NULL) {
//     // decide what to do?
//     graph = g;
//   }
//   graph = g;
// }