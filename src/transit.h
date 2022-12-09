<<<<<<< HEAD
/**
 * @file transit.h
 * @brief Implementation of the Transit class.
 *
 * @author Natalia Raymundi Pinheiro (natalia)
 * @date Fall 2023
 * @bug No known bugs.
 */

#pragma once

#include <boost/functional/hash.hpp> /* for hashing */
#include <iostream>                  /* for std::cout, std::endl */
#include <string>                    /* for std::string */
#include <unordered_map>             /* for std::map */
#include <unordered_set>
#include <vector> /* for std::vector */

using std::cout;
using std::endl;
using std::hash;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
class Transit {
private:
  class Bus {
  public:
    /** @brief Default Bus constutor.
     */
    Bus();

    /** @brief Parametrized Bus constructor.
     *
     *  @param new_route_id New bus_id.
     *  @param new_trip_id New trip_id.
     */
    Bus(string new_route_id, string new_trip_id);

    /** @brief Overloaded == operator.
     *
     *  @param other Compared Object.
     */
    bool operator==(const Bus &other) const {
      return (route_id == other.route_id && trip_id == other.trip_id);
    }

    /** @brief hashing class/function stolen from
     * https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
     * user jogojapan
     */
    struct BusHasher {
      size_t operator()(const Bus &b) const {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        size_t res = 17;
        res = res * 31 + hash<string>()(b.route_id);
        res = res * 31 + hash<string>()(b.trip_id);
        return res;
      }
    };

    /*
     * `route_id` from `trips.csv`.
     */
    string route_id;

    /*
     * `trip_id` from `trips.csv`.
     */
    string trip_id;
  };

  class Stop {
  public:
    /** @brief Default Stop constructor.
     */
    Stop();

    /** @brief Parametrized Bus constructor.
     *
     *  @param new_stop_id New stop_id.
     *  @param new_trip_id New trip_id.
     */
    Stop(string new_stop_id, string new_trip_id);

    /** @brief Overloaded == operator.
     *
     *  @param other Compared Object.
     */
    bool operator==(const Stop &other) const {
      return (stop_id == other.stop_id);
    }

    /** @brief hashing class/function stolen from
     * https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
     * user jogojapan
     */

    struct StopHasher {
      size_t operator()(const Stop &s) const {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        size_t res = 17;
        res = res * 31 + hash<string>()(s.stop_id);
        res = res * 31 + hash<string>()(s.trip_id);
        return res;
      }
    };

    /*
     * `stop_id` from `stop_times.csv`.
     */
    string stop_id;

    /*
     * `trip_id` from `stop_times.csv`.
     */
    // string trip_id;
    unordered_set<string> trip_ids;
  };

  /* @brief Default constructor.
   * moved here because of this?
   * https://stackoverflow.com/questions/10474417/how-to-delete-the-default-constructor
   */
  Transit();
  // helper split stringstream function
  // https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
  // Evan Teran
  void split(const string &s, char delim, vector<string> &result);
  vector<string> split(const string &s, char delim);

  /*
   * Vector storing all possible buses.
   */
  vector<Bus> buses;

  /*
   * Vector storing all possible buses.
   */
  vector<Stop> stops;

  /*
   * Map storing each bus and all the stops it goes
   * through chronologically.
   */
  unordered_map<Bus, vector<Stop>, Transit::Bus::BusHasher> bus_routes;

  /*
   * Map storing each stop and all the buses that go
   * through it chronologically.
   */
  unordered_map<Stop, vector<Bus>, Transit::Stop::StopHasher> bus_services;

public:
  /** @brief Parametrized constructor.
   *
   *  Initializes the member variables by reading an input CSV file.
   *
   *  @param trips `trips.csv`.
   *  @param stop_times `stop_times.csv`.
   */
  Transit(const string &trips_dataset, const string &stop_times_dataset);

  /** @brief Getter for buses.
   *
   *  @return buses.
   */
  vector<Bus> &getBuses();

  /** @brief Getter for stops.
   *
   *  @return stops.
   */
  vector<Stop> &getStops();

  /** @brief Getter for bus_routes.
   *
   *  @return bus_routes.
   */
  unordered_map<Bus, vector<Stop>, Transit::Bus::BusHasher> &getBusRoute();

  /** @brief Getter for bus_services.
   *
   *  @return bus_services.
   */
  unordered_map<Stop, vector<Bus>, Transit::Stop::StopHasher> &getBusService();

  /** @brief Find if Bus with bus_id and trip_id already exists.
   *
   *  @param bus_id bus_id to be found.
   *  @param trip_id trip_id to be found.
   *  @return index of Bus if found; otherwise, return -1.
   */
  int findInBuses(string bus_id, string trip_id);

  /** @brief Find if Stop with stop_id and trip_id already exists.
   *
   *  @param stop_id stop_id to be found.
   *  @param trip_id trip_id to be found.
   *  @return index of Stop if found; otherwise, return -1.
   */
  int findInStops(string stop_id, string trip_id);
=======
#pragma once

#include <string>   /* for std::string */
#include <vector>   /* for std::vector */

#include "../lib/edge.h"

using namespace std;


class Transit {
public:
    /** @brief Parametrixed constructor of Transit.
     * 
     *  @param stop_times_dataset 'stop_times.csv'.
     */
    Transit(const string& stop_times_dataset);

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

    /** @brief Calculate the time in seconds between two strings representing time.
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
    vector<Vertex>& getVertices();

    /** @brief Getter for edges.
     *
     *  @return edges.
     */
    vector<Edge>& getEdges();


private:
    /** @brief Default constructor of Transit.
     *         This is private because we don't want this to be used.
     */
    Transit() { /* Do nothing. */}
    
    /* 
     * Represents all created vertices.
     */
    vector<Vertex> vertices;
    
    /* 
     * Represents all created edges.
     */
    vector<Edge> edges;
>>>>>>> 4139d45d8766044bcfaed35b0eb776fbf2a000be
};