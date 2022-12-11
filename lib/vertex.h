#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/** @brief Vertex identify stops. Each vertex has a stop identification
 *         and a vector of routes that go through that stop.
 */
struct Vertex {
  /*
   * Represents the stop identification.
   */
  string stop;

  /** @brief Default constructor of Vertex.
   */
  Vertex() { /* Do nothing. */
  }

  /** @brief Parametrized constructor of Vertex.
   *         Creates a stop.
   *
   *  @param stop_ new stop identification.
   */
  Vertex(string stop_) : stop(stop_) {
    cout << "-> Created vertex with stop ID = " << stop << "." << endl;
  }

  /* Overloading operators */

  bool operator==(const Vertex &other) const { return (stop == other.stop); }

  bool operator<(const Vertex &other) const { return (stop < other.stop); }
};
