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
        Edge(double time_, Vertex new_start, Vertex new_edge): time(time_), cost_weight(0), direction("N"), 
            start(new_start), end(new_end), /*overall_time(0)*/, route("") {}
        
    };
private:
    // private data member to represent graph
    vector<vector<Edge>> graph;
    vector<Vertex> all_vertices;
    vector<Edge> all_edges;
};

#endif
