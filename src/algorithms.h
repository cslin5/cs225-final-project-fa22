#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "transit.h"

using std::map;
using std::string;
using std::vector;

class Algorithm {
public:
  // Constructor

  /** @brief Parametrized constructor for algorithm.
   *         Constructs a graph with a given vector of vertices and
   *         edges.
   *
   *  @param vertices_ vector of vertices parsed from dataset.
   *  @param edges_ vector of edges parsed from dataset.
   */
  Algorithm(vector<Vertex> vertices_, vector<Edge> edges_);

  /** @brief Fills the graph with information about the edges.
   *         This will end up connecting the vertices in the graph.
   */
  void buildGraph();

  // Getters

  /** @brief Getter for graph.
   *
   *  @return graph.
   */
  map<Vertex, map<Vertex, vector<Edge>>> &getGraph();

  // DFS to find connected vertices through routes

  bool RouteConnection(string route, Vertex origin, Vertex destination);

  Edge findEdge(string route, Vertex origin, Vertex destination);

  /** @brief Find Minimum Spanning Tree of bus stops based on time. Uses Prim's
   * algorithm */
  map<Vertex, map<Vertex, Edge>> Prim();

  /** @brief edge time comparison struct for priority queue */
  struct compareTime {
    constexpr bool operator()(Edge const &a, Edge const &b) const noexcept {
      return a.time > b.time;
    }
  };

  /** @brief Route Connection returns if there is a connection between
   *         a given stop to another stop using a certain route.
   *
   *  @param route Route ID.
   *  @param origin_stop Stop ID of origin.
   *  @param destination_stop Stop ID of destination.
   *  @return if we found a connection.
   */
  bool RouteConnection(string route, string origin_stop,
                       string destination_stop);

  /** @brief Helper for RouteConnetion.
   *
   *  @param route Route ID.
   *  @param origin Vertex origin.
   *  @param destination Vertex destination.
   *  @param visited Map that checks if certain Vertex was already visited.
   *  @return if we found a connection.
   */
  bool RouteConnectionHelper(string route, Vertex origin, Vertex destination,
                             map<Vertex, bool> &visited);

  /** @brief Finds the vertex in vertices with the given stop ID.
   *
   *  @param stop The stop ID to search for.
   *  @return the Vertex object with the given ID.
   */
  Vertex findVertex(string stop);

  vector<Edge> findOutgoingEdges(Vertex vertex);

  // // Tarjan's Algorithm

  /** @brief Tarjan's Algorithm.
   *         This is an algorithm used to find the strongly connected
   *         components of a graph.
   *
   *  @return the low-link value of the vertices.
   */
  map<Vertex, int> Tarjan();

  // Tarjan's Algorithm

  /** @brief Tarjan's Algorithm.
   *         This is an algorithm used to find the strongly connected
   *         components of a graph.
   *
   *  @return the low-link value of the vertices.
   */
  map<Vertex, int> Tarjan();

  /** @brief Tarjan's Algorithm helper.
   *         This is a recursive function that finds strongly
   *         connected components using a DFS traversal.
   *
   *  @param vertex The vertex to be visited next.
   *  @param ids The IDs of each vertex.
   *  @param low_link The low-link value of each vertex.
   *  @param on_stack Check if the vertex is on the stack.
   *  @param stack Stack containing the connected ancestors.
   *  @param sccCount The current number of strongly connected
   *         components.
   */
  void TarjanHelper(Vertex vertex, map<Vertex, int> &ids,
                    map<Vertex, int> &low_link, map<Vertex, bool> on_stack,
                    stack<Vertex> &stack, int &sccCount);

  // Getters

  vector<Vertex> &getVertices();
  vector<Edge> &getEdges();

private:
  /** @brief Default constructor for Algorithm.
   *         This is private because we don't want this to be used.
   */
  Algorithm() { /* Do nothing. */
  }

  /*
   * This is an weighted, directed adjacency matrix.
   * This constitutes the graph of stops (Vertices) and routes (Edges).
   */
  map<Vertex, map<Vertex, vector<Edge>>> graph;

  /*
   * Represents all stops (Vertices).
   */
  vector<Vertex> vertices;

  /*
   * Represents all routes (Edges).
   */
  vector<Edge> edges;
};
