#include <iostream>     /* for std::cout, std::endl */
#include <fstream>      /* for std::ifstream */
#include <sstream>      /* for std::stringstream */
#include <stdexcept>    /* for errors */
#include <time.h>       /* for time calculations */

#include "transit.h"

using namespace std;


Transit::Transit(const string& dataset) {
    // Dataset into an ifstream to be read.
    ifstream stop_times(dataset);

    // Make sure the file is open.
    if (stop_times.is_open()) {
        vector<vector<string>> data;
        string line;

        // Skip first line because it's just ID details.
        getline(stop_times, line);

        // Now, for each line:
        while (getline(stop_times, line)) {
            // Make line a stringstream to be read.
            stringstream ss(line);

            string field;
            vector<string> info;
            
            // Only get information with indexes 0, 1 and 3.
            // 0: route name;
            // 1: time;
            // 3: stop ID.
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
            // We need to create this before we create each edge
            // because edges have origin and destination vertices
            // (they depend on vertices).
            string stop_id = info.at(2);

            // Avoid duplicate stops.
            if (findVertex(stop_id) == -1) {
                vertices.push_back(Vertex(stop_id));
            }

            // Push this information to data, which will be used
            // to create edges.
            data.push_back(info);
        }

        // Now that all vertices were created, create all edges.
        createEdges(data);
    }
    
    // File could not be opened.
    else {
        throw std::runtime_error("File could not be opened.");
    }
}

void Transit::createEdges(vector<vector<string>> data) {
    // Starting at the second line of data:
    for (size_t line = 1; line < data.size(); line++) {
        // Save the first line.
        string route = data[line][0];
        
        // If it is the same route:
        if (data[line - 1][0] == route) {
            // Create an edge between them.
            Vertex origin = vertices[findVertex(data[line - 1][2])];
            Vertex destination = vertices[findVertex(data[line][2])];
            double time = findTime(data[line - 1][1], data[line][1]);

            edges.push_back(Edge(route, origin, destination, time));
        }
        
        // Else, it's not going to be the same route,
        // so we skip to the next route.
    }
}

int Transit::findVertex(string stop) {
    // Simple search function for vertex.
    for (size_t i = 0; i < vertices.size(); i++) {
        if (stop == vertices[i].stop) {
            // If we find the vertex, return its index.
            return i;
        }
    }

    // Else, return -1.
    return -1;
}

double Transit::findTime(string time1, string time2) {
    // Separate the time strings in ints.
    int tm_hour1 = stoi(time1.substr(0, 2));
    int tm_min1  = stoi(time1.substr(3, 2));
    int tm_sec1  = stoi(time1.substr(6, 2));

    int tm_hour2 = stoi(time2.substr(0, 2));
    int tm_min2  = stoi(time2.substr(3, 2));
    int tm_sec2  = stoi(time2.substr(6, 2));
    
    // Create a tm struct (time struct).
    struct tm time_tm1{};
    time_tm1.tm_hour = tm_hour1;
    time_tm1.tm_min  = tm_min1;
    time_tm1.tm_sec  = tm_sec1;
    
    struct tm time_tm2{};
    time_tm2.tm_hour = tm_hour2;
    time_tm2.tm_min  = tm_min2;
    time_tm2.tm_sec  = tm_sec2;

    // Convert tm struct to time_t (becomes time object).
    time_t time_convert1 = mktime(&time_tm1);
    time_t time_convert2 = mktime(&time_tm2);

    // Returns the difference between times!
    return difftime(time_convert2, time_convert1);
}

vector<Vertex>& Transit::getVertices() {
    return vertices;
}

vector<Edge>& Transit::getEdges() {
    return edges;
}