#include <fstream>   /* for ifstream */
#include <iostream>  /* for cout, endl */
#include <sstream>   /* for stringstream */
#include <stdexcept> /* for errors */
#include <time.h>    /* for time calculations */


#include "transit.h"

using namespace std;

Transit::Transit(const string &stop_times_dataset) {
  ifstream stop_times(stop_times_dataset);

  // trip_id: [@6.0.28929208@][32][1657992971959]/6__7W_#2_SHOW_HS_Early_Out
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
  int tm_min1 = stoi(time1.substr(3, 2));
  int tm_sec1 = stoi(time1.substr(6, 2));

  struct tm time_tm1 {};
  time_tm1.tm_hour = tm_hour1;
  time_tm1.tm_min = tm_min1;
  time_tm1.tm_sec = tm_sec1;

  time_t time_convert1 = mktime(&time_tm1);

  int tm_hour2 = stoi(time2.substr(0, 2));
  int tm_min2 = stoi(time2.substr(3, 2));
  int tm_sec2 = stoi(time2.substr(6, 2));

  struct tm time_tm2 {};
  time_tm2.tm_hour = tm_hour2;
  time_tm2.tm_min = tm_min2;
  time_tm2.tm_sec = tm_sec2;

  time_t time_convert2 = mktime(&time_tm2);

  // The order is weird too but has to be like this:
  return difftime(time_convert2, time_convert1);
}

vector<Vertex> &Transit::getVertices() { return vertices; }

vector<Edge> &Transit::getEdges() { return edges; }