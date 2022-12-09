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

TEST_CASE("Vertex (Simple) Test 1", "[vertex]") {
    cout << "\nVertex Test 1" <<  endl;
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


TEST_CASE("Vertex (Simple) Test 2", "[vertex]") {
    cout << "\nVertex Test 2" <<  endl;
    vector<Vertex> vertices(50);
    for (size_t i = 0; i < 50; i++) {
        vertices[i] = Vertex(to_string(i));
    }

    for (size_t i = 0; i < vertices.size(); i++) {
        REQUIRE(vertices[i].stop == to_string(i));
    }
}


TEST_CASE("Vertex + Edge (Simple) Test 1", "[vertex][edge]") {
    cout << "\nVertex + Edge Test 1" <<  endl;
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


/* TRANSIT */

double findTime(string time1, string time2) {
    cout << "Finding time from " << time1 << " to " << time2 << "... " << endl;

    int tm_hour1 = stoi(time1.substr(0, 2));
    int tm_min1  = stoi(time1.substr(3, 2));
    int tm_sec1  = stoi(time1.substr(6, 2));
    
    struct tm time_tm1{};
    time_tm1.tm_hour = tm_hour1;
    time_tm1.tm_min  = tm_min1;
    time_tm1.tm_sec  = tm_sec1;
    cout << "\ntime_tm1: " << time_tm1.tm_hour << '\t'
                           << time_tm1.tm_min << '\t'
                           << time_tm1.tm_sec << endl;

    time_t time_convert1 = mktime(&time_tm1);
    cout << asctime(&time_tm1) << endl;


    int tm_hour2 = stoi(time2.substr(0, 2));
    int tm_min2  = stoi(time2.substr(3, 2));
    int tm_sec2  = stoi(time2.substr(6, 2));
    
    struct tm time_tm2{};
    time_tm2.tm_hour = tm_hour2;
    time_tm2.tm_min  = tm_min2;
    time_tm2.tm_sec  = tm_sec2;
    cout << "\ntime_tm2: " << time_tm2.tm_hour << '\t'
                           << time_tm2.tm_min << '\t'
                           << time_tm2.tm_sec << endl;

    time_t time_convert2 = mktime(&time_tm2);
    cout << asctime(&time_tm2) << endl;

    // The order is weird too but has to be like this:
    return difftime(time_convert2, time_convert1);
}

TEST_CASE("findTime() Test 1", "[time]") {
    double time = findTime("14:00:00", "15:30:00");

    REQUIRE(time == (1*60*60 + 30*60));
}


TEST_CASE("Transit Test 1", "[transit][vertex][edge]") {
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


/* ALGORITHMS */

TEST_CASE("Algorithm Test 1", "[algorithm][transit][vertex][edge]") {
    cout << "\nAlgorithm Test 1" << endl;
    
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