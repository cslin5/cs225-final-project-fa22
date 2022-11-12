/**
 * @file transit.cpp
 * @brief Implementation of the Transit class.
 *
 * @author Natalia Raymundi Pinheiro (natalia)
 * @date Fall 2023
 * @bug No known bugs.
 */

#include "transit.h"

#include <ifstream>   /* for std::ifstream */
#include <sstream>    /* for std::stringstream */
#include <stdexcept>  /* for errors */

using std::ifstream;
using std::stringstream;


Transit::Transit() {
  /** Nothing to be done here. */
}

Transit::Transit(const string &trips_dataset, const string &stop_times_dataset) {
  /* BUSES */
  ifstream trips(trips_dataset);
  string bus_infos, bus_info;
  
  // If the file is open:
  if (trips.is_open()) {
    // For each line in the CSV file:
    while (getline(trips, bus_infos)) {
      stringstream ss(bus_infos);

      // Each "bus_infos" is an bus_info:
      string route_id;         // 0*
      // string service_id;    // 1
      string trip_id;          // 2*
      // string trip_headsign; // 3
      // string direction_id;  // 4
      // string block_id;      // 5
      // string shape_id;      // 6

      // For each bus_info in "bus_infos":
      int info_idx = 0;
      while (getline(ss, bus_info, ',')) {
        // Info represents route_id.
        if (info_idx == 0) {
          route_id = bus_info;
        }

        // Info represents trip_id.
        else if (info_idx == 2) {
          trip_id == bus_info;
        }

        // Increment info_idx to make sure we are going to the next bus_info.
        info_idx++;
      }

      // Do something with the extracted bus_infos:
      Bus bus(route_id, trip_id);
      // Push it to the vector of Buses:
      buses.push_back(bus);
      // Insert it into the map with an empty vector.
      bus_routes.insert(bus, vector<Stop>());
      
      /// @todo How do I insert the Stops into the map?
    }
  } else if (trips.fail()) {
    cout << "Coult not open trips.csv." << endl; return;
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
      string trip_id;            // 0*
      // string arrival_time;    // 1
      // string departure_time;  // 2
      string stop_id;            // 3*
      // string stop_sequence;   // 4
      // string stop_headsign;   // 5
      // string pickup_type;     // 6
      // string drop_off_type;   // 7

      // For each stop_times_info in "stop_times_infos":
      int info_idx = 0;
      while (getline(ss, stop_times_info, ',')) {
        // Info represents route_id.
        if (info_idx == 0) {
          trip_id = stop_times_info;
        }

        // Info represents trip_id.
        else if (info_idx == 3) {
          stop_id == stop_times_info;
        }

        // Increment info_idx to make sure we are going to the next stop_times_info.
        info_idx++;
      }

      // Do something with the extracted infos:
      Stop stop(stop_id, trip_id);
      // Push it to the vector of Stops:
      stops.push_back(stop);
      // Insert it into the map with an empty vector.
      bus_services.insert(stop, vector<Bus>());
      
      /// @todo How do I insert the Buses into the map?
    }
  } else if (stop_times.fail()) {
    cout << "Coult not open stop_times.csv." << endl; return;
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

vector<Bus> Transit::getBuses() { return buses; }

vector<Stop> Transit::getStops() { return stops; }

map<Bus, vector<Stop>> Transit::getBusRoute() { return bus_routes; }

map<Bus, vector<Stop>> Transit::getBusService() { return bus_services; }

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
