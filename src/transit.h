#pragma once

#include <string> /* for std::string */
#include <vector> /* for std::vector */

#include "../lib/edge.h"

using namespace std;

class Transit {
public:
  /** @brief Parametrized constructor of Transit.
   *
   *  @param stop_times_dataset 'stop_times.csv'.
   */
  Transit(const string &stop_times_dataset);

  /** @brief Creates all edges given existing vertices and
   *         parsed data.
   *
   *  @param data parsed data.
   */
  void createEdges(vector<vector<string>> data);

  /** @brief Finds vertex in vertices vector.
   *
   *  @param stop stop id to be searched
   *  @return found vertex.
   */
  int findVertex(string stop);

  /** @brief Calculate the time in seconds between two strings representing
   * time.
   *
   *  @param time1 first time.
   *  @param time2 second time.
   *  @return a double value that is the difference between times.
   */
  double findTime(string time1, string time2);

  /** @brief Getter for vertices.
   *
   *  @return vertices.
   */
  vector<Vertex> &getVertices();

  /** @brief Getter for edges.
   *
   *  @return edges.
   */
  vector<Edge> &getEdges();

private:
  /** @brief Default constructor of Transit.
   *         This is private because we don't want this to be used.
   */
  Transit() { /* Do nothing. */
  }

  /*
   * Represents all created vertices.
   */
  vector<Vertex> vertices;

  /*
   * Represents all created edges.
   */
  vector<Edge> edges;
};