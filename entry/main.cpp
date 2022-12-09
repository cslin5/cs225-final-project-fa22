#include <iostream>
#include <string>

#include "../src/transit.h"
#include "../src/algorithms.h"

using namespace std;


int main() {
    string file = "../dataset/stop_times.txt";
    
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Hello, user!" << endl;
    cout << "\nWe are going to analyze the data in '" << file << "'." << endl;

    cout << "First, create a Transit object to parse the data into Vertices and Edges Objects.\n" << endl;
    Transit transit(file);

    cout << "\nThen, we will save the parsed Vertices and Edges into vectors and pass";
    cout << "\tthem to an Algorithm constructor, which will create our graph.\n" << endl;
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();
    Algorithm algorithm(vertices, edges);

    cout << "Let's now visualize the graph!\n" << endl;
    map<Vertex, map<Vertex, vector<Edge>>> graph = algorithm.getGraph();


    for (pair<const Vertex, map<Vertex, vector<Edge>>> origin : graph) {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "origin: " << origin.first.stop << endl;
        for (pair<const Vertex, vector<Edge>> destination : origin.second) {
            cout << "\n\tdestination: " << destination.first.stop << endl;
            for (size_t i = 0; i < destination.second.size(); i++) {
                cout << "\t\tedge: {" << destination.second[i].route << ", " << destination.second[i].origin.stop
                        << ", " << destination.second[i].destination.stop << ", " << destination.second[i].time << " seconds}" << endl;
            }
        }
    }

    return 0;
}