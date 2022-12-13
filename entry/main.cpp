#include <iostream>
#include <string>

#include "../src/algorithms.h"
#include "../src/transit.h"

using namespace std;

int main() {
  string file = "../dataset/stop_times.txt";

  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
       << endl;
  cout << "Hello, user!" << endl;
  cout << "\nWe are going to analyze the data in '" << file << "'." << endl;

  cout << "First, create a Transit object to parse the data into Vertices and "
          "Edges Objects.\n"
       << endl;
  Transit transit(file);

  // cout << "Let's now visualize the graph!\n" << endl;
  // map<Vertex, map<Vertex, vector<Edge>>> graph = algorithm.getGraph();
  // for (pair<const Vertex, map<Vertex, vector<Edge>>> origin : graph) {
  //     cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  //     cout << "origin: " << origin.first.stop << endl;
  //     for (pair<const Vertex, vector<Edge>> destination : origin.second) {
  //         cout << "\n\tdestination: " << destination.first.stop << endl;
  //         for (size_t i = 0; i < destination.second.size(); i++) {
  //             cout << "\t\tedge: {" << destination.second[i].route << ", " <<
  //             destination.second[i].origin.stop
  //                     << ", " << destination.second[i].destination.stop << ",
  //                     " << destination.second[i].time << " seconds}" << endl;
  //         }
  //     }
  // }

  // RouteConnection()
  //   algorithm.RouteConnection(
  //       "[@124.0.143437300@][31][1591365669945]/0__L2_NO_SCH_MF",
  //       "WRTWASH:4", "WRTCHCH:4");

  // Tarjan()
  //   algorithm.Tarjan();

  return 0;
}
