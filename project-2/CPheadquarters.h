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

    void read_edges(std::string path);

    void read_stations(std::string path);


    Graph getGraph() const;

    void heuristic(string path[], unsigned int &nodesVisited, double &totalDistance, string id);

    void heuristicRec(Vertex *v, string path[], unsigned int currentIndex, double distance, unsigned int &nodesVisited, double &totalDistance);

    void chooseRoute();

    void print3();


    void backtrack();
};


#endif //PROJECT_2_CPHEADQUARTERS_H
