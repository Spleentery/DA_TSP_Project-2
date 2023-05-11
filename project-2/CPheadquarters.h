//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_CPHEADQUARTERS_H
#define PROJECT_2_CPHEADQUARTERS_H


#include "Graph.h"
#include "Station.h"

class CPheadquarters {
    Graph graph;
    unordered_map<string, Station> stations;
public:

    void read_network(std::string path);

    void read_stations(std::string path);

    void read_files();

    Graph getGraph() const;

    double heuristic(string path[]);

    double heuristicRec(Vertex *v, string path[], unsigned int currentIndex, double distance);

    void print3();
};


#endif //PROJECT_2_CPHEADQUARTERS_H
