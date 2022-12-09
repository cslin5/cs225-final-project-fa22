<<<<<<< HEAD
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

using std::getline;
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

  // If the file is open:
  if (trips.is_open()) {
    // For each line in the CSV file:

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

    string line;
    // get rid of the first line
    getline(trips, line);
    // For each line in the CSV file:
    while (getline(trips, line)) {
      vector<string> data = split(line, ',');
      // not valid if less than 3 entries
      if (data.size() > 2) {
        // Info represents route_id.
        route_id = data.at(0);

        // Info represents trip_id.
        trip_id = data.at(2);
      }

      // Do something with the extracted bus_infos:
      Bus bus(route_id, trip_id); 
      // Push it to the vector of Buses:
      buses.push_back(bus);
      // Insert it into the map with an empty vector.
      bus_routes.insert(pair<Bus, vector<Stop>>(bus, vector<Stop>()));
    }
  } else if (trips.fail()) {
    cout << "Could not open " << trips_dataset << endl;
    return;
  }

  /* STOPS */
  ifstream stop_times(stop_times_dataset);

  // If the file is open:
  if (stop_times.is_open()) {
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

    string line;
    // get rid of the first line
    getline(stop_times, line);
    // For each line in the CSV file:
    while (getline(stop_times, line)) {

      vector<string> data = split(line, ',');
      // not valid if less than 4 entries
      if (data.size() > 3) {
        // Info represents trip_id.
        trip_id = data.at(0);

        // Info represents stop_id.
        stop_id = data.at(3);
      }

      // Do something with the extracted infos:
      Stop stop(stop_id, trip_id);
      // Push it to the vector of Stops:
      stops.push_back(stop);
      // Insert it into the map with an empty vector.
      bus_services.insert(pair<Stop, vector<Bus>>(stop, vector<Bus>()));
    }
  } else if (stop_times.fail()) {
    cout << "Could not open " << stop_times_dataset << endl;
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
    if (buses[i].route_id == bus_id && buses[i].trip_id == trip_id) {
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

Transit::Bus::Bus() : route_id(""), trip_id("") { /* Nothing to be done here. */
}

Transit::Bus::Bus(const string new_route_id, const string new_trip_id)
    : route_id(new_route_id), trip_id(new_trip_id) {
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
=======
#include <iostream>     /* for cout, endl */
#include <fstream>      /* for ifstream */
#include <sstream>      /* for stringstream */
#include <stdexcept>    /* for errors */
#include <time.h>       /* for time calculations */

#include "transit.h"

using namespace std;


Transit::Transit(const string& stop_times_dataset) {
    ifstream stop_times(stop_times_dataset);

    // trip_id:         [@6.0.28929208@][32][1657992971959]/6__7W_#2_SHOW_HS_Early_Out
    // arrival_time:    14:48:00
    // stop_id:         EMS:9
    if (stop_times.is_open()) {
        vector<vector<string>> data;
        
        string line;
        getline(stop_times, line); // Skip first line.
        while (getline(stop_times, line)) {
            
            stringstream ss(line);
            string field;
            vector<string> info;
            
            int index = 0;
            while (getline(ss, field, ',')) {
                if (index == 0 || index == 1 || index == 3) {
                    info.push_back(field);
                }

                if (index == 3) {
                    break;
                }

                index++;
            }

            // Create every vertex.
            // We need to create this before we create each edge because edges have
            // origin and destination vertices.
            string stop_id = info[2];
            if (findVertex(stop_id) == -1) {
                // Avoids duplicate stops.
                vertices.push_back(Vertex(stop_id));
            }

            data.push_back(info);
        }

        createEdges(data);
    }

}

void Transit::createEdges(vector<vector<string>> data) {
    // field = 0: trip_id
    // field = 1: arrival_time
    // field = 2: stop_id
    for (size_t line = 1; line < data.size(); line++) {
        string route = data[line][0];
        
        // If it is the same route:
        if (data[line - 1][0] == route) {
            Vertex origin = vertices[findVertex(data[line - 1][2])];
            Vertex destination = vertices[findVertex(data[line][2])];
            double time = findTime(data[line - 1][1], data[line][1]);

            edges.push_back(Edge(route, origin, destination, time));
        }

        // If this is starting a new route:
        else {
            // Skip this one!
        }

    }
}

int Transit::findVertex(string stop) {
    for (size_t i = 0; i < vertices.size(); i++) {
        if (stop == vertices[i].stop) {
            return i;
        }
    }
    return -1;
}

double Transit::findTime(string time1, string time2) {
    int tm_hour1 = stoi(time1.substr(0, 2));
    int tm_min1  = stoi(time1.substr(3, 2));
    int tm_sec1  = stoi(time1.substr(6, 2));
    
    struct tm time_tm1{};
    time_tm1.tm_hour = tm_hour1;
    time_tm1.tm_min  = tm_min1;
    time_tm1.tm_sec  = tm_sec1;
    
    time_t time_convert1 = mktime(&time_tm1);


    int tm_hour2 = stoi(time2.substr(0, 2));
    int tm_min2  = stoi(time2.substr(3, 2));
    int tm_sec2  = stoi(time2.substr(6, 2));
    
    struct tm time_tm2{};
    time_tm2.tm_hour = tm_hour2;
    time_tm2.tm_min  = tm_min2;
    time_tm2.tm_sec  = tm_sec2;

    time_t time_convert2 = mktime(&time_tm2);

    // The order is weird too but has to be like this:
    return difftime(time_convert2, time_convert1);
}

vector<Vertex>& Transit::getVertices() {
    return vertices;
}

vector<Edge>& Transit::getEdges() {
    return edges;
>>>>>>> 4139d45d8766044bcfaed35b0eb776fbf2a000be
}