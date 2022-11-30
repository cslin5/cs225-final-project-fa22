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
#include <vector>                    /* for std::vector */

using std::cout;
using std::endl;
using std::hash;
using std::string;
using std::unordered_map;
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
     *  @param new_bus_id New bus_id.
     *  @param new_bus_id New trip_id.
     */
    Bus(string new_bus_id, string new_trip_id);

    /** @brief Overloaded == operator.
     *
     *  @param other Compared Object.
     */
    bool operator==(const Bus &other) const {
      return (bus_id == other.bus_id && trip_id == other.trip_id);
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
        res = res * 31 + hash<string>()(b.bus_id);
        res = res * 31 + hash<string>()(b.trip_id);
        return res;
      }
    };

    /*
     * `route_id` from `trips.csv`.
     */
    string bus_id;

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
     *  @param new_bus_id New trip_id.
     */
    Stop(string new_stop_id, string new_trip_id);

    /** @brief Overloaded == operator.
     *
     *  @param other Compared Object.
     */
    bool operator==(const Stop &other) const {
      return (stop_id == other.stop_id && trip_id == other.trip_id);
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
    string trip_id;
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
};