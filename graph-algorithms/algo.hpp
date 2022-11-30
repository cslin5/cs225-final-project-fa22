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
    };
    struct Edge {
        double cost_weight;
        double distance;
        Vertex start;
        Vertex end;
        // Direction (upper), route
        string direction;
        Edge(Vertex new_start, Vertex new_edge): cost_weight(0), distance(0), direction("N"), start(new_start), end(new_end) {}
    };
private:
    // private data member to represent graph
    vector<vector<Edge>> graph;
   
};

#endif
