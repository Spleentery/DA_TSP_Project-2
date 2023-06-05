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


    /**
     * Calculates the total cost of the TSP problem using a 2-approximation strategy.
     * Firstly running a variation of prim's algorithn with complexity O((V+E)logV).
     * Then running a DFS algorithm (pathRec()) with complexity O(E)
     * And finally adding the distances between all the nodes, worst case complexity O(E*E)
     * @attention Time Complexity: O((V+E)logV + 2E)
     */
    void triangular_Approximation_Heuristic();

    /**
     * Generates a pre-order path of the MST using a DFS strategy, storing their indexes in a vector
     * @param vertex
     * @attention Time Complexity: O(E)
     */
    void pathRec(Vertex *vertex);

    /**
     * Translates degrees to radians
     * @param degrees
     * @return
     * @attention Time Complexity: O(1)
     */
    double degToRad(double degrees);

    /**
     * Returns the distance between two points using their coordinates in kilometers
     * @param latitude1
     * @param longitude1
     * @param latitude2
     * @param longitude2
     * @return
     * @attention Time Complexity: O(1)
     */
    double haversineDistance(double latitude1, double longitude1, double latitude2, double longitude2);

    /**
     * Returns the distance between the nodes with indexes id=a and id=b.
     * If their distance is not explicit in the edges, then it is calculated using the haversineDistance() function, if possible.
     * @param a
     * @param b
     * @return
     * @attention Time Complexity: O(E)
     */
    double getDist(int a, int b);

    /**
     * Sorts all the nodes in order of the angle they do with the middle point and calculates the total distance required trough the noddes in that order
     * @attention Time Complexity: O(nlog(n))
     */
    void raquel();

    /**
     * Calculates the angle between the vectors BA and BC
     * @attention Time Complexity: O(1)
     */
    double calculateAngle(double Ax, double Ay, double Bx, double By, double Cx, double Cy);
};


#endif //PROJECT_2_CPHEADQUARTERS_H
