#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <time.h>       /* for time calculations */

#include "../src/transit.h"
#include "../src/algorithms.h"
#include "../tests/tests.h"

using namespace std;


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

TEST_CASE("Find time between strings of time", "[time]") {
    Transit transit;
    double time = transit.findTime("14:00:00", "15:30:00");

    REQUIRE(time == (1*60*60 + 30*60));
}


TEST_CASE("Transit Constructor Test 1", "[transit][vertex][edge]") {
    cout << "\nTransit Test 1" << endl;

    Transit transit("../tests/example_dataset.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    REQUIRE(vertices.size() == 4);
    REQUIRE(edges.size() == 8);

    REQUIRE(vertices[0].stop == "A");
    REQUIRE(vertices[1].stop == "B");
    REQUIRE(vertices[2].stop == "C");
    REQUIRE(vertices[3].stop == "D");

    REQUIRE(edges[0].route == "Grey");
    REQUIRE(edges[0].origin.stop == "A");
    REQUIRE(edges[0].destination.stop == "B");
    REQUIRE(edges[0].time == 60);
    
    REQUIRE(edges[1].route == "Grey");
    REQUIRE(edges[1].origin.stop == "B");
    REQUIRE(edges[1].destination.stop == "C");
    REQUIRE(edges[1].time == 2*60);

    REQUIRE(edges[2].route == "Grey");
    REQUIRE(edges[2].origin.stop == "C");
    REQUIRE(edges[2].destination.stop == "D");
    REQUIRE(edges[2].time == 3*60);


    REQUIRE(edges[3].route == "Teal");
    REQUIRE(edges[3].origin.stop == "A");
    REQUIRE(edges[3].destination.stop == "C");
    REQUIRE(edges[3].time == 60);

    REQUIRE(edges[4].route == "Teal");
    REQUIRE(edges[4].origin.stop == "C");
    REQUIRE(edges[4].destination.stop == "B");
    REQUIRE(edges[4].time == 2*60);


    REQUIRE(edges[5].route == "Blue");
    REQUIRE(edges[5].origin.stop == "A");
    REQUIRE(edges[5].destination.stop == "D");
    REQUIRE(edges[5].time == 60);

    REQUIRE(edges[6].route == "Blue");
    REQUIRE(edges[6].origin.stop == "D");
    REQUIRE(edges[6].destination.stop == "C");
    REQUIRE(edges[6].time == 2*60);

    REQUIRE(edges[7].route == "Blue");
    REQUIRE(edges[7].origin.stop == "C");
    REQUIRE(edges[7].destination.stop == "B");
    REQUIRE(edges[7].time == 3*60);
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

TEST_CASE("Route Connection - Grey","[grey][routeconnection][algorithm][transit][vertex][edge]") {
    cout << "\nRoute Connection - Grey" << endl;

    Transit transit("../tests/example_dataset.txt");

    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();
    
    Algorithm algorithm(vertices, edges);

    // There are general and edge cases mixed here:
    REQUIRE(algorithm.RouteConnection("Grey", "A", "B") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "A", "C") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "A", "D") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "B", "C") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "B", "D") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "C", "D") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "D", "D") == true);
    REQUIRE(algorithm.RouteConnection("Grey", "B", "A") == false);
    REQUIRE(algorithm.RouteConnection("Grey", "C", "A") == false);
    REQUIRE(algorithm.RouteConnection("Grey", "D", "A") == false);
}

TEST_CASE("Route Connection - Teal","[teal][routeconnection][algorithm][transit][vertex][edge]") {
    cout << "\nRoute Connection - Teal" << endl;

    Transit transit("../tests/example_dataset.txt");

    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();
    
    Algorithm algorithm(vertices, edges);

    // There are general and edge cases mixed here:
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

TEST_CASE("Route Connection - Blue","[blue][routeconnection][algorithm][transit][vertex][edge]") {
    cout << "\nRoute Connection - Blue" << endl;

    Transit transit("../tests/example_dataset.txt");

    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();
    
    Algorithm algorithm(vertices, edges);

    // There are general and edge cases mixed here:
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

TEST_CASE("Prim Test 1", "[prim][algorithm][transit][vertex][edge]") {
    cout << "\nPrim Test 1" << endl;

    Transit transit("../tests/prim1.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    REQUIRE(vertices.size() == 4);
    REQUIRE(edges.size() == 16);

    Algorithm algorithm(vertices, edges);
    auto mst = algorithm.Prim();

    REQUIRE(mst.size() == 1);
    REQUIRE(mst[Vertex("A")].size() == 3);
}

TEST_CASE("Prim Test 2", "[prim][algorithm][transit][vertex][edge]") {
    cout << "\nPrim Test 2" << endl;

    Transit transit("../tests/prim2.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    REQUIRE(vertices.size() == 4);
    REQUIRE(edges.size() == 16);

    Algorithm algorithm(vertices, edges);
    auto mst = algorithm.Prim();

    REQUIRE(mst.size() == 2);
    REQUIRE(mst[Vertex("A")].size() == 2);
    REQUIRE(mst[Vertex("B")].size() == 1);
}

TEST_CASE("Prim Test 3", "[prim][algorithm][transit][vertex][edge]") {
    cout << "\nPrim Test 3" << endl;
    
    Transit transit("../tests/prim3.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    REQUIRE(vertices.size() == 12);
    REQUIRE(edges.size() == 21);

    Algorithm algorithm(vertices, edges);
    auto mst = algorithm.Prim();

    REQUIRE(mst.size() == 8);
    REQUIRE(mst[Vertex("1")].size() == 1);
    REQUIRE(mst[Vertex("2")].size() == 1);
    REQUIRE(mst[Vertex("3")].size() == 2);
    REQUIRE(mst[Vertex("4")].size() == 0);
    REQUIRE(mst[Vertex("5")].size() == 2);
    REQUIRE(mst[Vertex("6")].size() == 1);
    REQUIRE(mst[Vertex("8")].size() == 1);
    REQUIRE(mst[Vertex("9")].size() == 0);
    REQUIRE(mst[Vertex("10")].size() == 1);
    REQUIRE(mst[Vertex("11")].size() == 1);
}

TEST_CASE("Tarjan Test 1", "[tarjan][algorithm][transit][vertex][edge]") {
    cout << "\nTarjan Test 1" << endl;
    
    Transit transit("../tests/tarjan1.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    Algorithm algorithm(vertices, edges);

    map<Vertex, int> expected;
    Vertex v0 = Vertex("0"); expected[v0] = 0;
    Vertex v1 = Vertex("1"); expected[v1] = 0;
    Vertex v2 = Vertex("2"); expected[v2] = 0;
    Vertex v3 = Vertex("3"); expected[v3] = 0;
    Vertex v4 = Vertex("4"); expected[v4] = 0;

    map<Vertex, int> tarjan = algorithm.Tarjan();
    REQUIRE(expected.size() == tarjan.size());
    
    for (auto& pair : expected) {
        REQUIRE(tarjan[pair.first] == pair.second);
    }
}

TEST_CASE("Tarjan Test 2", "[tarjan][algorithm][transit][vertex][edge]") {
    cout << "\nTarjan Test 2" << endl;

    Transit transit("../tests/tarjan2.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    Algorithm algorithm(vertices, edges);
    
    map<Vertex, int> expected;
    Vertex v0 = Vertex("0"); expected[v0] = 5;
    Vertex v1 = Vertex("1"); expected[v1] = 5;
    Vertex v2 = Vertex("2"); expected[v2] = 5;
    Vertex v3 = Vertex("3"); expected[v3] = 8;
    Vertex v4 = Vertex("4"); expected[v4] = 9;

    map<Vertex, int> tarjan = algorithm.Tarjan();
    REQUIRE(expected.size() == tarjan.size());
    
    for (auto& pair : expected) {
        REQUIRE(tarjan[pair.first] == pair.second);
    }
}

TEST_CASE("Tarjan Test 3", "[tarjan][algorithm][transit][vertex][edge]") {
    cout << "\nTarjan Test 3" << endl;

    Transit transit("../tests/tarjan3.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    Algorithm algorithm(vertices, edges);
    
    map<Vertex, int> expected;
    Vertex v0 = Vertex("0"); expected[v0] = 10;
    Vertex v1 = Vertex("1"); expected[v1] = 11;
    Vertex v2 = Vertex("2"); expected[v2] = 12;
    Vertex v3 = Vertex("3"); expected[v3] = 13;

    map<Vertex, int> tarjan = algorithm.Tarjan();
    REQUIRE(expected.size() == tarjan.size());
    
    for (auto& pair : expected) {
        REQUIRE(tarjan[pair.first] == pair.second);
    }
}

TEST_CASE("Tarjan Test 4", "[tarjan][algorithm][transit][vertex][edge]") {
    cout << "\nTarjan Test 4" << endl;
    
    Transit transit("../tests/tarjan4.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    Algorithm algorithm(vertices, edges);

    map<Vertex, int> expected;
    Vertex v0 = Vertex("0"); expected[v0] = 14;
    Vertex v1 = Vertex("1"); expected[v1] = 14;
    Vertex v2 = Vertex("2"); expected[v2] = 14;
    Vertex v3 = Vertex("3"); expected[v3] = 17;
    Vertex v4 = Vertex("4"); expected[v4] = 19;
    Vertex v5 = Vertex("5"); expected[v5] = 18;
    Vertex v6 = Vertex("6"); expected[v6] = 20;

    map<Vertex, int> tarjan = algorithm.Tarjan();
    REQUIRE(expected.size() == tarjan.size());
    
    for (auto& pair : expected) {
        REQUIRE(tarjan[pair.first] == pair.second);
    }
}

TEST_CASE("Tarjan Test 5", "[tarjan][algorithm][transit][vertex][edge]") {
    cout << "\nTarjan Test 5" << endl;
    
    Transit transit("../tests/tarjan5.txt");
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();

    Algorithm algorithm(vertices, edges);

    map<Vertex, int> expected;
    Vertex v0 = Vertex("0"); expected[v0] = 21;
    Vertex v1 = Vertex("1"); expected[v1] = 21;
    Vertex v2 = Vertex("2"); expected[v2] = 21;
    Vertex v3 = Vertex("3"); expected[v3] = 30;
    Vertex v4 = Vertex("4"); expected[v4] = 24;
    Vertex v5 = Vertex("5"); expected[v5] = 24;
    Vertex v6 = Vertex("6"); expected[v6] = 24;
    Vertex v7 = Vertex("7"); expected[v7] = 27;
    Vertex v8 = Vertex("8"); expected[v8] = 28;
    Vertex v9 = Vertex("9"); expected[v9] = 28;
    Vertex v10 = Vertex("10"); expected[v10] = 31;

    map<Vertex, int> tarjan = algorithm.Tarjan();
    REQUIRE(expected.size() == tarjan.size());
    
    for (auto& pair : expected) {
        REQUIRE(tarjan[pair.first] == pair.second);
    }
}