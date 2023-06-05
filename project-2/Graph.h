//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_GRAPH_H
#define PROJECT_2_GRAPH_H


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>


#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    /**
    * Auxiliary function to find a vertex with a given ID.
    * @param id
    * @return vertex pointer to vertex with given content, or nullptr if not found
    */
    Vertex *findVertex(long id) const;

    /**
     *  Adds a vertex with a given content or info (in) to a graph (this).
     * @param id
     * @return true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(long id);

    /**
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @param sourc
     * @param dest
     * @param w
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(long sourc, long dest, double d);




    [[nodiscard]] int getNumVertex() const;

    [[nodiscard]] std::unordered_map<long,Vertex *> getVertexSet() const;

    /**
     * prints the graph
     */
    void print() const;



    /**
     * Check if the graph has a Hamiltonian cycle.
     * (visit all nodes only once and return to the starting node)
     * If it has, return the minimum cost cycle.
     * conditions:
     * - graph must be connected
     * - graph must not have pendant vertices
     * - graph must not have articulation points
     * @attention Time Complexity: O(n!)
     * @note TSP is NP-hard problem, application to large graphs is infeasible
     * @param shortestPath
     * @param shortestPathCost
     * @return true if the graph has a Hamiltonian cycle, false otherwise
     */
    bool TSP(std::vector<Vertex *> &shortestPath, double &shortestPathCost);

    /**
     * Check if the graph has a Hamiltonian cycle.
     * conditions:
     * - graph must be connected
     * - graph must not have pendant vertices
     * - graph must not have articulation points
     * @attention Time Complexity: O(n!)
     * @note Hamiltonian Cycle problem is NP-complete
     * @param path
     * @param pathCost
     * @return
     */
    bool hasHamiltonianCycle(std::vector<Vertex *> &path, double &pathCost);

protected:
    std::unordered_map<long,Vertex *> vertexSet;    // vertex set

    double **distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    // for Tarjan's algorithm
    std::vector<int> disc, low, parent;
    std::vector<bool> visited, ap;


    /**
     * delete a vertex from the graph, making a subgraph from a graph
     * @param name
     */
    void deleteVertex(long name);

    /**
     * calculate the cost of the path
     * @param path
     * @return double
     */
    double getPathCost(const std::vector<Vertex *> &path);
    /**
     * Utility function to solve the TSP problem
     * @param v
     * @param path
     * @param shortestPath
     * @param shortestPathCost
     * @param numOfPossiblePaths
     * @return
     */
    bool TSPUtil(Vertex *v, std::vector<Vertex *> &path, std::vector<Vertex *> &shortestPath, double &shortestPathCost,
                 int &numOfPossiblePaths, double &currentCost);
    /**
     * Utility function to check if the graph has a Hamiltonian cycle.
     * @param v
     * @param path
     * @param pathCost
     * @return double
     */
    double hasHamiltonianCycleUtil(Vertex *v, std::vector<Vertex *> &path, double &pathCost);

    /**
     * Function to check for pendant vertices in the graph
     * @attention Time complexity: O(V)   (linear)
     * @return true if the graph has pendant vertices, false otherwise
     */
    bool hasPendantVertex();

    /**
     * use Tarjan’s Algorithm to find articulation points
     * @attention Time Complexity: O(V + E)  (linear)
     * @return true/false
     */
    bool hasArticulationPoint();

    /**
     * Utility function to check if the graph contains a articulation point.
     * @param pCurrentVertex
     * @param time
     * @return true/false
     */
    bool hasArticulationPointUtil(Vertex *pCurrentVertex, int time);
};

void deleteMatrix(int **m, int n);

void deleteMatrix(double **m, int n);


#endif //PROJECT_2_GRAPH_H
