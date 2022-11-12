/**
 * @file transit.h
 * @brief Implementation of the Transit class.
 *
 * @author Natalia Raymundi Pinheiro (natalia)
 * @date Fall 2023
 * @bug No known bugs.
 */

#pragma once

#include <iostream> /* for std::cout, std::endl */
#include <map>      /* for std::map */
#include <string>   /* for std::string */
#include <vector>   /* for std::vector */

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;


class Transit {
public:
  /** @brief Default constructor.
   */
  Transit();

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
  vector<Bus> getBuses();

  /** @brief Getter for stops.
   *
   *  @return stops.
   */
  vector<Stop> getStops();

  /** @brief Getter for bus_route.
   *
   *  @return bus_route.
   */
  map<Bus, vector<Stop>> getBusRoute();

  /** @brief Getter for bus_service.
   *
   *  @return bus_service.
   */
  map<Bus, vector<Stop>> getBusService();

  /** @brief Find if Bus with bus_id and trip_id already exists.
   *  
   *  @param buses Vector of buses.
   *  @param bus_id bus_id to be found.
   *  @param trip_id trip_id to be found.
   *  @return index of Bus if found; otherwise, return -1.
   */
  int find(const vector<Bus> buses, const string bus_id, const string trip_id);

  /** @brief Find if Stop with stop_id and trip_id already exists.
   *  
   *  @param stops Vector of stops.
   *  @param stop_id stop_id to be found.
   *  @param trip_id trip_id to be found.
   *  @return index of Stop if found; otherwise, return -1.
   */
  int find(const vector<Bus> stops, const string stop_id, const string trip_id);

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
    Bus(const string new_bus_id, const string new_trip_id);
    
    /*
     * `route_id` from `trips.csv`.
     */
    const string bus_id;

    /*
     * `trip_id` from `trips.csv`.
     */
    const string trip_id;
  }

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
    Stop(const string new_stop_id, const string new_trip_id);

    /*
     * `stop_id` from `stop_times.csv`.
     */
    const string stop_id;

    /*
     * `trip_id` from `stop_times.csv`.
     */
    const string trip_id;
  }

  /*
   * Vector storing all possible buses.
   */
  const vector<Bus> buses;

  /*
   * Vector storing all possible buses.
   */
  const vector<Stop> stops;

  /*
   * Map storing each bus and all the stops it goes
   * through chronologically.
   */
  const map<Bus, vector<Stop>> bus_route;

  /*
   * Map storing each stop and all the buses that go
   * through it chronologically.
   */
  const map<Stop, vector<Bus>> bus_service;

};