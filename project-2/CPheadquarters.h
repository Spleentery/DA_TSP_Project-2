//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_CPHEADQUARTERS_H
#define PROJECT_2_CPHEADQUARTERS_H


#include "Graph.h"

using namespace std;

class CPheadquarters {
    Graph graph;
    vector<long> mst_preorder_path;
public:

    void read_edges(std::string path);

    void read_coordinates(std::string path);


    Graph getGraph() const;

    /**
     * Initial part of the algorithm, finds the route of the vertex with the given id, calling the recursive function
     * @param route
     * @param nodesVisited
     * @param totalDistance
     * @param id
     */
    void heuristic(long path[], unsigned int &nodesVisited, double &totalDistance, long id);

    /**
     * Recursive part of the heuristic that looks for the closest vertex to the actual one,
     * the closest vertex is determine using the angle, so this heuristic uses geological information from the vertex
     * @param v
     * @param route
     * @param currentIndex
     * @param distance
     * @param nodesVisited
     * @param totalDistance
     * @attention the time complexity of this part of the heuristic is O(E)
     */
    void heuristicRec(Vertex *v, long path[], unsigned int currentIndex, double distance, unsigned int &nodesVisited, double &totalDistance);

    /**
     * Iterates through all vertex to determine with which one to starts
     * @note this algorithm only work when it starts in some specifics vertex
     * so that's the reason it needs to go through all possible nodes to choose the one who satisfies the needs of the problem
     * @attention since this parte of the heuristic iterates through all vertex and call the recursive part from the algorithm that is O(E) the time complexity is O(EV)
     */
    void chooseRoute();


    /**
     * Use a backtracking exhaustive approach for TSP
     * Applicable only for very small graphs
     */
    void backtrack();

    void hamiltonianCycle();

    void triangular_Approximation_Heuristic();

    void pathRec(Vertex *vertex);

    double degToRad(double degrees);

    double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    double getDist(int a, int b);
};


#endif //PROJECT_2_CPHEADQUARTERS_H
