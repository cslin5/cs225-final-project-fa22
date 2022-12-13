#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <time.h> /* for time calculations */
#include <vector>

#include "../src/algorithms.h"
#include "../src/transit.h"
#include "../tests/tests.h"

using std::string;
using std::vector;

/* VERTEX AND EDGES */

TEST_CASE("Vertex Constructor Test 1", "[vertex]") {
  vector<string> stops({"A", "B", "C", "D"});

  vector<Vertex> vertices(stops.size());
  for (size_t i = 0; i < stops.size(); i++) {
    vertices[i] = Vertex(stops[i]);
  }

  REQUIRE(vertices[0].stop == "A");
  REQUIRE(vertices[1].stop == "B");
  REQUIRE(vertices[2].stop == "C");
  REQUIRE(vertices[3].stop == "D");
}

TEST_CASE("Vertex Constructor Test 2", "[vertex]") {
  vector<Vertex> vertices(50);
  for (size_t i = 0; i < 50; i++) {
    vertices[i] = Vertex(to_string(i));
  }

  for (size_t i = 0; i < vertices.size(); i++) {
    REQUIRE(vertices[i].stop == to_string(i));
  }
}

TEST_CASE("Vertex & Edge Constructor Test 1", "[vertex][edge]") {
  vector<string> stops({"A", "B", "C", "D"});

  vector<Vertex> vertices(stops.size());
  for (size_t i = 0; i < stops.size(); i++) {
    vertices[i] = Vertex(stops[i]);
  }

  vector<Edge> edges;
  // Grey: A -> B -> C -> D (3 edges)
  edges.push_back(Edge("Grey", vertices[0], vertices[1], 120));
  edges.push_back(Edge("Grey", vertices[1], vertices[2], 130));
  edges.push_back(Edge("Grey", vertices[2], vertices[3], 150));

  // Teal: A -> C -> B (2 edges)
  edges.push_back(Edge("Teal", vertices[0], vertices[2], 90));
  edges.push_back(Edge("Teal", vertices[2], vertices[1], 80));

  REQUIRE(edges.size() == 5);

  REQUIRE(edges[0].route == "Grey");
  REQUIRE(edges[0].origin.stop == "A");
  REQUIRE(edges[0].destination.stop == "B");
  REQUIRE(edges[0].time == 120);

  REQUIRE(edges[1].route == "Grey");
  REQUIRE(edges[1].origin.stop == "B");
  REQUIRE(edges[1].destination.stop == "C");
  REQUIRE(edges[1].time == 130);

  REQUIRE(edges[2].route == "Grey");
  REQUIRE(edges[2].origin.stop == "C");
  REQUIRE(edges[2].destination.stop == "D");
  REQUIRE(edges[2].time == 150);

  REQUIRE(edges[3].route == "Teal");
  REQUIRE(edges[3].origin.stop == "A");
  REQUIRE(edges[3].destination.stop == "C");
  REQUIRE(edges[3].time == 90);

  REQUIRE(edges[4].route == "Teal");
  REQUIRE(edges[4].origin.stop == "C");
  REQUIRE(edges[4].destination.stop == "B");
  REQUIRE(edges[4].time == 80);
}

// /* TRANSIT */

double findTime(string time1, string time2) {
  cout << "Finding time from " << time1 << " to " << time2 << "... " << endl;

  int tm_hour1 = stoi(time1.substr(0, 2));
  int tm_min1 = stoi(time1.substr(3, 2));
  int tm_sec1 = stoi(time1.substr(6, 2));

  struct tm time_tm1 {};
  time_tm1.tm_hour = tm_hour1;
  time_tm1.tm_min = tm_min1;
  time_tm1.tm_sec = tm_sec1;
  cout << "\ntime_tm1: " << time_tm1.tm_hour << '\t' << time_tm1.tm_min << '\t'
       << time_tm1.tm_sec << endl;

  time_t time_convert1 = mktime(&time_tm1);
  cout << asctime(&time_tm1) << endl;

  int tm_hour2 = stoi(time2.substr(0, 2));
  int tm_min2 = stoi(time2.substr(3, 2));
  int tm_sec2 = stoi(time2.substr(6, 2));

  struct tm time_tm2 {};
  time_tm2.tm_hour = tm_hour2;
  time_tm2.tm_min = tm_min2;
  time_tm2.tm_sec = tm_sec2;
  cout << "\ntime_tm2: " << time_tm2.tm_hour << '\t' << time_tm2.tm_min << '\t'
       << time_tm2.tm_sec << endl;

  time_t time_convert2 = mktime(&time_tm2);
  cout << asctime(&time_tm2) << endl;

  // The order is weird too but has to be like this:
  return difftime(time_convert2, time_convert1);
}

TEST_CASE("findTime() Test 1", "[time]") {
  double time = findTime("14:00:00", "15:30:00");

  REQUIRE(time == (1 * 60 * 60 + 30 * 60));
}

TEST_CASE("Transit Constructor Test 1", "[transit][vertex][edge]") {
  cout << "\nTransit Test 1" << endl;

  Transit transit("../tests/example_dataset.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  REQUIRE(vertices.size() == 4);
  REQUIRE(edges.size() == 8);

  cout << "\nVertex:" << endl;
  for (Vertex vertex : vertices) {
    cout << "  * " << vertex.stop << endl;
  }

  REQUIRE(vertices[0].stop == "A");
  REQUIRE(vertices[1].stop == "B");
  REQUIRE(vertices[2].stop == "C");
  REQUIRE(vertices[3].stop == "D");

  cout << "\nEdges:" << endl;
  for (Edge edge : edges) {
    cout << "  * " << edge.route << endl;
  }

  REQUIRE(edges[0].route == "Grey");
  REQUIRE(edges[0].origin.stop == "A");
  REQUIRE(edges[0].destination.stop == "B");
  REQUIRE(edges[0].time == 60);

  REQUIRE(edges[1].route == "Grey");
  REQUIRE(edges[1].origin.stop == "B");
  REQUIRE(edges[1].destination.stop == "C");
  REQUIRE(edges[1].time == 2 * 60);

  REQUIRE(edges[2].route == "Grey");
  REQUIRE(edges[2].origin.stop == "C");
  REQUIRE(edges[2].destination.stop == "D");
  REQUIRE(edges[2].time == 3 * 60);

  REQUIRE(edges[3].route == "Teal");
  REQUIRE(edges[3].origin.stop == "A");
  REQUIRE(edges[3].destination.stop == "C");
  REQUIRE(edges[3].time == 60);

  REQUIRE(edges[4].route == "Teal");
  REQUIRE(edges[4].origin.stop == "C");
  REQUIRE(edges[4].destination.stop == "B");
  REQUIRE(edges[4].time == 2 * 60);

  REQUIRE(edges[5].route == "Blue");
  REQUIRE(edges[5].origin.stop == "A");
  REQUIRE(edges[5].destination.stop == "D");
  REQUIRE(edges[5].time == 60);

  REQUIRE(edges[6].route == "Blue");
  REQUIRE(edges[6].origin.stop == "D");
  REQUIRE(edges[6].destination.stop == "C");
  REQUIRE(edges[6].time == 2 * 60);

  REQUIRE(edges[7].route == "Blue");
  REQUIRE(edges[7].origin.stop == "C");
  REQUIRE(edges[7].destination.stop == "B");
  REQUIRE(edges[7].time == 3 * 60);
}

// /* ALGORITHMS */

TEST_CASE("Building Algorithm Test 1", "[algorithm][transit][vertex][edge]") {
  cout << "\nBuilding Algorithm Test 1" << endl;

  Transit transit("../tests/example_dataset.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);
  map<Vertex, map<Vertex, vector<Edge>>> graph = algorithm.getGraph();

  for (pair<const Vertex, map<Vertex, vector<Edge>>> origin : graph) {
    for (pair<const Vertex, vector<Edge>> destination : origin.second) {
      for (size_t i = 0; i < destination.second.size(); i++) {
        REQUIRE(origin.first == destination.second[i].origin);
        REQUIRE(destination.first == destination.second[i].destination);
      }
    }
  }
}

// TEST_CASE("Tarjan Test 1", "[tarjan][algorithm][transit][vertex][edge]") {
//     cout << "\nTarjan Test 1" << endl;

//     Transit transit("../tests/example2_dataset.txt");
//     vector<Vertex> vertices = transit.getVertices();
//     vector<Edge> edges = transit.getEdges();

//     Algorithm algorithm(vertices, edges);

//     algorithm.Tarjan();
// }

TEST_CASE("Tarjan Test 2", "[tarjan][algorithm][transit][vertex][edge]") {
  cout << "\nTarjan Test 2" << endl;
  cout << "Geeks for Geeks: SCC in firth graph." << endl;

  Transit transit("../tests/geeksforgeeks5.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  map<Vertex, int> expected;
  Vertex v0 = Vertex("0");
  expected[v0] = 0;
  Vertex v1 = Vertex("1");
  expected[v1] = 0;
  Vertex v2 = Vertex("2");
  expected[v2] = 0;
  Vertex v3 = Vertex("3");
  expected[v3] = 0;
  Vertex v4 = Vertex("4");
  expected[v4] = 0;

  // map<Vertex, int> tarjan = algorithm.Tarjan();
  // REQUIRE(expected.size() == tarjan.size());

  // for (auto &pair : expected) {
  //   REQUIRE(tarjan[pair.first] == pair.second);
  // }
}

TEST_CASE("Tarjan Test 3", "[tarjan][algorithm][transit][vertex][edge]") {
  cout << "\nTarjan Test 3" << endl;
  cout << "Geeks for Geeks: SCC in first graph." << endl;

  Transit transit("../tests/geeksforgeeks1.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  map<Vertex, int> expected;
  Vertex v0 = Vertex("0");
  expected[v0] = 0;
  Vertex v1 = Vertex("1");
  expected[v1] = 0;
  Vertex v2 = Vertex("2");
  expected[v2] = 0;
  Vertex v3 = Vertex("3");
  expected[v3] = 3;
  Vertex v4 = Vertex("4");
  expected[v4] = 4;

  map<Vertex, int> tarjan = algorithm.Tarjan();
  REQUIRE(expected.size() == tarjan.size());

  for (auto &pair : expected) {
    REQUIRE(tarjan[pair.first] == pair.second);
  }
}

TEST_CASE("Tarjan Test 4", "[tarjan][algorithm][transit][vertex][edge]") {
  cout << "\nTarjan Test 4" << endl;
  cout << "Geeks for Geeks: SCC in second graph." << endl;

  Transit transit("../tests/geeksforgeeks2.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  map<Vertex, int> expected;
  Vertex v0 = Vertex("0");
  expected[v0] = 0;
  Vertex v1 = Vertex("1");
  expected[v1] = 1;
  Vertex v2 = Vertex("2");
  expected[v2] = 2;
  Vertex v3 = Vertex("3");
  expected[v3] = 3;

  map<Vertex, int> tarjan = algorithm.Tarjan();
  REQUIRE(expected.size() == tarjan.size());

  for (auto &pair : expected) {
    REQUIRE(tarjan[pair.first] == pair.second);
  }
}

TEST_CASE("Tarjan Test 5", "[tarjan][algorithm][transit][vertex][edge]") {
  cout << "\nTarjan Test 5" << endl;
  cout << "Geeks for Geeks: SCC in third graph." << endl;

  Transit transit("../tests/geeksforgeeks3.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  map<Vertex, int> expected;
  Vertex v0 = Vertex("0");
  expected[v0] = 0;
  Vertex v1 = Vertex("1");
  expected[v1] = 0;
  Vertex v2 = Vertex("2");
  expected[v2] = 0;
  Vertex v3 = Vertex("3");
  expected[v3] = 3;
  Vertex v4 = Vertex("4");
  expected[v4] = 5;
  Vertex v5 = Vertex("5");
  expected[v5] = 4;
  Vertex v6 = Vertex("6");
  expected[v6] = 6;

  map<Vertex, int> tarjan = algorithm.Tarjan();
  REQUIRE(expected.size() == tarjan.size());

  for (auto &pair : expected) {
    REQUIRE(tarjan[pair.first] == pair.second);
  }
}

TEST_CASE("Tarjan Test 6", "[tarjan][algorithm][transit][vertex][edge]") {
  cout << "\nTarjan Test 6" << endl;
  cout << "Geeks for Geeks: SCC in four graph." << endl;

  Transit transit("../tests/geeksforgeeks4.txt");
  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  map<Vertex, int> expected;
  Vertex v0 = Vertex("0");
  expected[v0] = 0;
  Vertex v1 = Vertex("1");
  expected[v1] = 0;
  Vertex v2 = Vertex("2");
  expected[v2] = 0;
  Vertex v3 = Vertex("3");
  expected[v3] = 9; // Should be either 0 or 9
  Vertex v4 = Vertex("4");
  expected[v4] = 3;
  Vertex v5 = Vertex("5");
  expected[v5] = 3;
  Vertex v6 = Vertex("6");
  expected[v6] = 3;
  Vertex v7 = Vertex("7");
  expected[v7] = 6;
  Vertex v8 = Vertex("8");
  expected[v8] = 7;
  Vertex v9 = Vertex("9");
  expected[v9] = 7;
  Vertex v10 = Vertex("10");
  expected[v10] = 10;

  map<Vertex, int> tarjan = algorithm.Tarjan();
  REQUIRE(expected.size() == tarjan.size());

  for (auto &pair : expected) {
    REQUIRE(tarjan[pair.first] == pair.second);
  }
}

TEST_CASE("Route Connection - Grey",
          "[grey][routeconnection][algorithm][transit][vertex][edge]") {
  cout << "\nRoute Connection - Grey" << endl;

  Transit transit("../tests/example_dataset.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  REQUIRE(algorithm.RouteConnection("Grey", "A", "B") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "A", "C") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "A", "D") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "B", "C") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "B", "D") == true); //
  REQUIRE(algorithm.RouteConnection("Grey", "C", "D") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "D", "D") == true);
  REQUIRE(algorithm.RouteConnection("Grey", "B", "A") == false);
  REQUIRE(algorithm.RouteConnection("Grey", "C", "A") == false);
  REQUIRE(algorithm.RouteConnection("Grey", "D", "A") == false);
}

TEST_CASE("Route Connection - Teal",
          "[teal][routeconnection][algorithm][transit][vertex][edge]") {
  cout << "\nRoute Connection - Teal" << endl;

  Transit transit("../tests/example_dataset.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  REQUIRE(algorithm.RouteConnection("Teal", "A", "B") == true);
  REQUIRE(algorithm.RouteConnection("Teal", "A", "C") == true);
  REQUIRE(algorithm.RouteConnection("Teal", "B", "B") == true);
  REQUIRE(algorithm.RouteConnection("Teal", "B", "C") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "B", "D") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "A", "D") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "C", "D") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "D", "D") == true);
  REQUIRE(algorithm.RouteConnection("Teal", "B", "A") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "C", "A") == false);
  REQUIRE(algorithm.RouteConnection("Teal", "D", "A") == false);
}

TEST_CASE("Route Connection - Blue",
          "[blue][routeconnection][algorithm][transit][vertex][edge]") {
  cout << "\nRoute Connection - Blue" << endl;

  Transit transit("../tests/example_dataset.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  Algorithm algorithm(vertices, edges);

  REQUIRE(algorithm.RouteConnection("Blue", "A", "B") == true);
  REQUIRE(algorithm.RouteConnection("Blue", "A", "C") == true);
  REQUIRE(algorithm.RouteConnection("Blue", "B", "B") == true);
  REQUIRE(algorithm.RouteConnection("Blue", "B", "C") == false);
  REQUIRE(algorithm.RouteConnection("Blue", "B", "D") == false);
  REQUIRE(algorithm.RouteConnection("Blue", "A", "D") == true);
  REQUIRE(algorithm.RouteConnection("Blue", "C", "D") == false);
  REQUIRE(algorithm.RouteConnection("Blue", "D", "D") == true);
  REQUIRE(algorithm.RouteConnection("Blue", "B", "A") == false);
  REQUIRE(algorithm.RouteConnection("Blue", "C", "A") == false);
  REQUIRE(algorithm.RouteConnection("Blue", "D", "A") == false);
}

TEST_CASE("Prim's", "[prim]") {
  Transit transit("../tests/example_prim.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  REQUIRE(vertices.size() == 4);
  REQUIRE(edges.size() == 16);

  Algorithm algorithm(vertices, edges);

  auto mst = algorithm.Prim();
  REQUIRE(mst.size() == 1);
  REQUIRE(mst[Vertex("A")].size() == 3);
}

TEST_CASE("Prim's 2", "[prim]") {
  Transit transit("../tests/example_prim2.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  REQUIRE(vertices.size() == 4);
  REQUIRE(edges.size() == 16);

  Algorithm algorithm(vertices, edges);

  auto mst = algorithm.Prim();

  for (auto p : mst) {
    cout << p.first.stop << ": " << endl;

    for (auto e : p.second) {
      cout << e.second.origin.stop << "->" << e.second.destination.stop << endl;
    }
    cout << endl;
  }

  REQUIRE(mst.size() == 2);
  REQUIRE(mst[Vertex("A")].size() == 2);
  REQUIRE(mst[Vertex("B")].size() == 1);
}

TEST_CASE("Big Prim's", "[prim]") {
  Transit transit("../tests/example_bigprim.txt");

  vector<Vertex> vertices = transit.getVertices();
  vector<Edge> edges = transit.getEdges();

  REQUIRE(vertices.size() == 12);
  REQUIRE(edges.size() == 21);

  Algorithm algorithm(vertices, edges);

  auto mst = algorithm.Prim();

  for (auto p : mst) {
    cout << p.first.stop << ": " << endl;

    for (auto e : p.second) {
      cout << e.second.origin.stop << "->" << e.second.destination.stop << endl;
    }
    cout << endl;
  }

  REQUIRE(mst.size() == 9);
  REQUIRE(mst[Vertex("1")].size() == 1);
  REQUIRE(mst[Vertex("2")].size() == 1);
  REQUIRE(mst[Vertex("4")].size() == 1);
  REQUIRE(mst[Vertex("3")].size() == 1);
  REQUIRE(mst[Vertex("5")].size() == 2);
  REQUIRE(mst[Vertex("6")].size() == 1);
  REQUIRE(mst[Vertex("8")].size() == 1);
  REQUIRE(mst[Vertex("9")].size() == 2);
  REQUIRE(mst[Vertex("10")].size() == 1);
}
