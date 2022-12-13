#include <iostream>
#include <string>
#include <fstream>

#include "../src/transit.h"
#include "../src/algorithms.h"

using namespace std;


int main() {
    string file = "../dataset/stop_times.txt";
    
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Hello, user!" << endl;
    cout << "\nWe are going to analyze the data in '" << file << "'." << endl;

    cout << "\nFirst, create a Transit object to parse the data into Vertices and Edges Objects.\n" << endl;
    Transit transit(file);

    cout << "\nThen, we will save the parsed Vertices and Edges into vectors and pass";
    cout << "\tthem to an Algorithm constructor, which will create our graph.\n" << endl;
    vector<Vertex> vertices = transit.getVertices();
    vector<Edge> edges = transit.getEdges();
    Algorithm algorithm(vertices, edges);


    // cout << "Let's now visualize the graph!\n" << endl;

    // ofstream graphVisualization;
    // graphVisualization.open("../results/all_data/graph_visualization.txt");

    // map<Vertex, map<Vertex, vector<Edge>>> graph = algorithm.getGraph();
    // for (pair<const Vertex, map<Vertex, vector<Edge>>> origin : graph) {
    //     graphVisualization << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //     graphVisualization << "origin: " << origin.first.stop << endl;
    //     for (pair<const Vertex, vector<Edge>> destination : origin.second) {
    //         graphVisualization << "\n\tdestination: " << destination.first.stop << endl;
    //         for (size_t i = 0; i < destination.second.size(); i++) {
    //             graphVisualization << "\t\tedge: {" << destination.second[i].route << ", " << destination.second[i].origin.stop
    //                     << ", " << destination.second[i].destination.stop << ", " << destination.second[i].time << " seconds}" << endl;
    //         }
    //     }
    // }

    // graphVisualization.close();


    // RouteConnection()
    // cout << "\n Now, let's test RouteConnection(), our DFS traversal." << endl;

    // ofstream dfs;
    // dfs.open("../results/all_data/dfs_results.txt");

    // vector<string> routes;
    // for (Edge edge : algorithm.getEdges()) {
    //     if (find(routes.begin(), routes.end(), edge.route) == routes.end()) {
    //         routes.push_back(edge.route);
    //     }
    // }

    // for (Vertex v1 : algorithm.getVertices()) {
    //     for (Vertex v2 : algorithm.getVertices()) {
    //         if (v1.stop != v2.stop) {
    //             for (string route : routes) {
    //                 dfs << "Is there a connection between " << v1.stop <<
    //                         " and " << v2.stop << " through route " << route << "?\t\t";
    //                 bool result = algorithm.RouteConnection(route, v1.stop, v2.stop);
    //                 dfs << (result ? "YES." : "NO.") << endl << endl;
    //             }
    //         }
    //     }
    // }

    // dfs.close();
    
    // ofstream dfs_less_route;
    // dfs_less_route.open("../results/all_data/dfs_less_route.txt");

    // string route = "[@6.0.28929208@][32][1657992971959]/6__7W_#2_SHOW_HS_Early_Out";
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         string origin = vertices[i].stop;
    //         string destination = vertices[j].stop;
            
    //         if (origin != destination) {
    //             dfs_less_route << "Is there a connection between " << origin << " and " << destination << " through route " << route << "?\t\t";
                
    //             bool result = algorithm.RouteConnection(route, origin, destination);
    //             dfs_less_route << (result ? "YES." : "NO.") << endl << endl;   
    //         }
    //     }
    // }


    // dfs_less_route.close();

    
    // Tarjan()

    // cout << "\nRouteConnection() is done; let's move on to Tarjan's Algorithm." << endl;

    // ofstream tarjan;
    // tarjan.open("../results/all_data/tarjan_results.txt");

    // map<Vertex, int> low_link = algorithm.Tarjan();

    // for (auto& pair : low_link) {
    //     tarjan << (pair.first).stop << ":\t\t" << pair.second << endl;
    // }
    
    // tarjan.close();
    

    return 0;
}