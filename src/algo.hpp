#ifndef ALGO_HPP
#define ALGO_HPP

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Algo {
public:
    Algo(vector<vector<int>> g);
    void DijSolve();
    void translate_data(vector<Bus> buses);
    void build_graph();
    bool DFS_connected_on_route(string route_, string start_, string end_);

    struct Vertex {
        // represent stops as Direction of stop -- follows typical cardinal directions (if true N, S, E, W then do double letters), Stop Name
        string stop;
        vector<string> routes;

        bool addRoute(string new_route){
            if(routes.find(new_route) == routes.end()){
                routes.push_back(new_route);
                return true;
            }
            return false;
        }
        Vertex(){}
        Vertex(string stop_) : stop(stop_){}
    };
    struct Edge {
        double cost_weight;
        double time;
        Vertex start;
        Vertex end;
        // double overall_time;
        string route; 
        // Direction (upper), route
        string direction;
        Edge(){}
        Edge(double time_, string route_, Vertex new_start, Vertex new_edge): time(time_), cost_weight(0), direction("N"), 
            start(new_start), end(new_end), /*overall_time(0)*/, route(route_) {}
        
    };
private:
    // private data member to represent graph
    map<Vertex, map<Vertex, vector<Edge>>> graph;
    vector<Vertex> all_vertices;
    vector<Edge> all_edges;
};

#endif
