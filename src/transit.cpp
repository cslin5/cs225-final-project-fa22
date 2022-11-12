/**
 * @file transit.cpp
 * @brief Implementation of the Transit class.
 *
 * @author Natalia Raymundi Pinheiro (natalia)
 * @date Fall 2023
 * @bug No known bugs.
 */

#include "transit.h"

#include <ifstream> /* for std::ifstream */

using std::ifstream;


Transit::Transit() {
  /** Nothing to be done here. */
}

Transit::Transit(const string &trips_dataset, const string &stop_times_dataset) {
  /* BUSES */
  ifstream trips(trips_dataset);
  string bus_info;
  
  if (trips.is_open()) {
    while (getline(trips, bus_info)) {
      /* Do something. */
    }
  }


  /* STOPS */
  ifstream stop_times(stop_times_dataset);
  string stop_info;
  
  if (stop_times.is_open()) {
    while (getline(stop_times, stop_info)) {
      /* Do something. */
    }
  }

}

vector<Bus> Transit::getBuses() { return buses; }

vector<Stop> Transit::getStops() { return stops; }

map<Bus, vector<Stop>> Transit::getBusRoute() { return bus_route; }

map<Bus, vector<Stop>> Transit::getBusService() { return bus_service; }

int Transit::find(const vector<Bus> buses, const string bus_id, const string trip_id) {
  // For each Bus in buses:
  for (int i = 0; i < buses.size(); i++) {
    // If Bus is found, return its index.
    if (buses[i].bus_id == bus_id && buses[i].trip_id == trip_id) {
      return i;
    }
  }
  
  // If not found, return -1.
  return -1;
}

int Transit::find(const vector<Stop> stops, const string stop_id, const string trip_id) {
  // For each Bus in buses:
  for (int i = 0; i < stops.size(); i++) {
    // If Bus is found, return its index.
    if (stops[i].stop_id == stop_id && stops[i].trip_id == trip_id) {
      return i;
    }
  }
  
  // If not found, return -1.
  return -1;
}

/* Implementation for Bus class */

Transit::Bus::Bus(): bus_id(""), trip_id("") {
  /* Nothing to be done here. */
}

Transit::Bus::Bus(const string new_bus_id, const string new_trip_id):
      bus_id(new_bus_id), trip_id(new_trip_id) {

  // To avoid creating duplicates,
  // if Bus does not exist already:
  if (find(buses, new_bus_id, new_trip_id) == -1) {
    bus_id  = new_stop_id;
    trip_id = new_trip_id;
  }
}


/* Implementation for Stop class */

Transit::Stop::Stop(): stop_id(""), trip_id("") {
  /* Nothing to be done here. */
}

Transit::Stop::Stop(const string new_stop_id, const string new_trip_id):
      bus_id(new_stop_id), trip_id(new_trip_id) {

  // To avoid creating duplicates,
  // if Stop does not exist already:
  if (find(stops, new_stop_id, new_trip_id) == -1) {
    stop_id = new_stop_id;
    trip_id = new_trip_id;
  }
}
