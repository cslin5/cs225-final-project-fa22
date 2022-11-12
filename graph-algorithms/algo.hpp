#ifndef ALGO_HPP
#define ALGO_HPP

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Algo {
public:
    Algo(vector<vector<int>> g);
    void PrimsSolve();

private:
    // private data memebr to represent graph
    vector<vector<int>> graph;
};

#endif
