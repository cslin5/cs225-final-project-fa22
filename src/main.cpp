#include <iostream>
#include "algo.hpp"

int main() {
   Vertex v1();
   Vertex v2();
   Vertex v3();

   vector<Vertex> vertex_vec = vector<Vertex>();
   vertex_vec.push_back(v1);
   vertex_vec.push_back(v2);
   vertex_vec.push_back(v3);

   Edge e1(v1, v2);
   Edge e2(v1, v3);
   Edge e3(v2, v3);

   vector<Edge> edge_vec = vector<Edge>();
   edge_vec.push_back(e1);
   edge_vec.push_back(e2);
   edge_vec.push_back(e3);

   std::cout<< graph.size() << std::endl;
}