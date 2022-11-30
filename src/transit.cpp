/**
 * @file transit.cpp
 * @brief Implementation of the Transit class.
 *
 * @author Natalia Raymundi Pinheiro (natalia)
 * @date Fall 2023
 * @bug Bugs in Transit constructor.
 */

#include "transit.h"

#include <boost/functional/hash.hpp>
#include <fstream>   /* for ifstream */
#include <sstream>   /* for std::stringstream */
#include <stdexcept> /* for errors */

using std::ifstream;
using std::pair;
using std::stringstream;

// Transit::Transit() { /** Nothing to be done here. */
// }

/** @bug In this function. We might have to create a template for map.
 *       It seems that the problem is in map comparisons, but I don't
 *       know why it is making comparisions.
 *       I'm (natalia) not really sure what will fix the problem.
 */
Transit::Transit(const string &trips_dataset,
                 const string &stop_times_dataset) {
  /* BUSES */
  ifstream trips(trips_dataset);
  string bus_infos, bus_info;

  // If the file is open:
  if (trips.is_open()) {
    // For each line in the CSV file:
    while (getline(trips, bus_infos)) {
      stringstream ss(bus_infos);

      // Each "bus_infos" is an bus_info:
      string route_id; // 0*
      // string service_id;    // 1
      string trip_id; // 2*
      // string trip_headsign; // 3
      // string direction_id;  // 4
      // string block_id;      // 5
      // string shape_id;      // 6

      // For each bus_info in "bus_infos":
      int info_idx = 0;
      while (getline(ss, bus_info)) {
        vector<string> data = split(ss.str(), ',');
        // not valid if less than 3 entries
        if (data.size() > 2) {
          // Info represents route_id.
          route_id = data.at(0);

          // Info represents trip_id.
          trip_id = data.at(2);
        }
      }

      // Do something with the extracted bus_infos:
      Bus bus(route_id, trip_id);
      // Push it to the vector of Buses:
      buses.push_back(bus);
      // Insert it into the map with an empty vector.
      bus_routes.insert(pair<Bus, vector<Stop>>(bus, vector<Stop>()));

      /// @todo How do I insert the Stops into the map? i think i fixed?
    }
  } else if (trips.fail()) {
    cout << "Could not open trips.csv." << endl;
    return;
  }

  /* STOPS */
  ifstream stop_times(stop_times_dataset);
  string stop_times_infos, stop_times_info;

  // If the file is open:
  if (stop_times.is_open()) {
    // For each line in the CSV file:
    while (getline(stop_times, stop_times_infos)) {
      stringstream ss(stop_times_infos);

      // Each "stop_times_infos" is an stop_times_info:
      string trip_id; // 0*
      // string arrival_time;    // 1
      // string departure_time;  // 2
      string stop_id; // 3*
      // string stop_sequence;   // 4
      // string stop_headsign;   // 5
      // string pickup_type;     // 6
      // string drop_off_type;   // 7

      // For each stop_times_info in "stop_times_infos":
      int info_idx = 0;
      while (getline(ss, stop_times_info, ',')) {

        vector<string> data = split(ss.str(), ',');
        // not valid if less than 4 entries
        if (data.size() > 3) {
          // Info represents route_id.
          trip_id = data.at(0);

          // Info represents trip_id.
          stop_id = data.at(3);
        }
      }

      // Do something with the extracted infos:
      Stop stop(stop_id, trip_id);
      // Push it to the vector of Stops:
      stops.push_back(stop);
      // Insert it into the map with an empty vector.
      bus_services.insert(pair<Stop, vector<Bus>>(stop, vector<Bus>()));

      /// @todo How do I insert the Buses into the map?
    }
  } else if (stop_times.fail()) {
    cout << "Coult not open stop_times.csv." << endl;
    return;
  }

  // After we have read all the data:

  // For each bus,
  for (Bus bus : buses) {
    // and for each stop,
    for (Stop stop : stops) {
      // if their trip_ids match,
      if (bus.trip_id == stop.trip_id) {
        // insert stop in the bus_routes map;
        bus_routes[bus].push_back(stop);
        // insert bus in the bus_service map.
        bus_services[stop].push_back(bus);
      }
    }
  }
}

vector<Transit::Bus> &Transit::getBuses() { return buses; }

vector<Transit::Stop> &Transit::getStops() { return stops; }

unordered_map<Transit::Bus, vector<Transit::Stop>, Transit::Bus::BusHasher> &
Transit::getBusRoute() {
  return bus_routes;
}

unordered_map<Transit::Stop, vector<Transit::Bus>, Transit::Stop::StopHasher> &
Transit::getBusService() {
  return bus_services;
}

int Transit::findInBuses(string bus_id, string trip_id) {
  // For each Bus in buses:
  for (unsigned i = 0; i < buses.size(); i++) {
    // If Bus is found, return its index.
    if (buses[i].bus_id == bus_id && buses[i].trip_id == trip_id) {
      return i;
    }
  }

  // If not found, return -1.
  return -1;
}

int Transit::findInStops(string stop_id, string trip_id) {
  // For each Bus in buses:
  for (unsigned i = 0; i < stops.size(); i++) {
    // If Bus is found, return its index.
    if (stops[i].stop_id == stop_id && stops[i].trip_id == trip_id) {
      return i;
    }
  }

  // If not found, return -1.
  return -1;
}

/* Implementation for Bus class */

Transit::Bus::Bus() : bus_id(""), trip_id("") { /* Nothing to be done here. */
}

Transit::Bus::Bus(const string new_bus_id, const string new_trip_id)
    : bus_id(new_bus_id), trip_id(new_trip_id) {
  /* Nothing to be done here. */
}

/* Implementation for Stop class */

Transit::Stop::Stop() : stop_id(""), trip_id("") {
  /* Nothing to be done here. */
}

Transit::Stop::Stop(const string new_stop_id, const string new_trip_id)
    : stop_id(new_stop_id), trip_id(new_trip_id) {
  /* Nothing to be done here. */
}

void Transit::split(const string &s, char delim, vector<string> &result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, item, delim)) {
    result.push_back(item);
  }
}

vector<string> Transit::split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}