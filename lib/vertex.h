#pragma once

#include <iostream> /* for std::cout, std::endl */
#include <string>   /* for std::string */
#include <vector>   /* for std::vector */

using std::cout;
using std::endl;
using std::string;
using std::vector;

/** @brief A Vertex represents a bus stop.
 *         Each vertex has a stop ID in string format.
 */
struct Vertex {
  /*
   * Bus stop identification.
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

  /** @brief Parametrized constructor of Vertex.
   *         Creates a vertex with given stop ID.
   *
   *  @param stop_ Stop ID of new Vertex.
   */
  Vertex(string stop_) : stop(stop_) {
    cout << "-> Created vertex with stop ID = " << stop << "." << endl;
  }

  bool operator==(const Vertex &other) const { return (stop == other.stop); }

  /* Operator Overloading */

  /** @brief Overloading comparison operator '=='.
   *
   *  @param other Vertex to be compared to.
   *  @return if vertices have equal stop IDs.
   */
  bool operator==(const Vertex &other) const { return (stop == other.stop); }

  /** @brief Overloading comparison operator '=='.
   *
   *  @param other Vertex to be compared to.
   *  @return if vertices have equal stop IDs.
   */
  bool operator<(const Vertex &other) const { return (stop < other.stop); }
};
