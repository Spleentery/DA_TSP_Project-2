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


#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    /**
    * Auxiliary function to find a vertex with a given ID.
    * @param id
    * @return vertex pointer to vertex with given content, or nullptr if not found
    */
    Vertex *findVertex(const std::string &id) const;

    /**
     *  Adds a vertex with a given content or info (in) to a graph (this).
     * @param id
     * @return true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const std::string &id);

    /**
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @param sourc
     * @param dest
     * @param w
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &sourc, const std::string &dest, double d);




    [[nodiscard]] int getNumVertex() const;

    [[nodiscard]] std::vector<Vertex *> getVertexSet() const;

    /**
     * prints the graph
     */
    void print() const;

    /**
     * finds the maximum flow in the graph, given a source and a target
     * @param s
     * @param t
     * @return maximum flow
     * @note The Edmonds-Karp algorithm is a special case of the Ford-Fulkerson algorithm.
     * @note It uses Breadth-First Search to find the augmenting paths with the minimum number of edges
     * @attention The time complexity of the Edmonds-Karp algorithm is O(V*E^2), where V is the number of vertices and E is the number of edges in the graph.
     */
    int edmondsKarp(const std::string &s, const std::string &t);

    /**
     * finds all the source vertexes of the entire graph
     * @return vector with the id's of the source vertexes
     */
    std::vector<std::string> getSources();

    /**
     * finds all the target vertexes of the entire graph
     * @return vector with the id's of the target vertexes
     */
    std::vector<std::string> getTargets();

    /**
     * finds the maximum flow in the graph, given a set of sources and a set of targets
     * @param souces
     * @param targets
     * @return maximum flow
     */
    int mul_edmondsKarp(std::vector<std::string> souces, std::vector<std::string> targets);

    /**
     * finds all the source vertexes of a sub_graph
     * @param desired_stations
     * @return vector with the id's of the target vertexes
     */
    std::vector<std::string> find_sources(std::vector<std::string> desired_stations);

    /**
     * finds all the target vertexes of a sub_graph
     * @param desired_stations
     * @return vector with the id's of the target vertexes
     */
    std::vector<std::string> find_targets(std::vector<std::string> desired_stations);

    /**
     * finds all existing paths for a given source and destination
     * return a vector of paths as an out parameter
     * @param source
     * @param destination
     * @param path
     * @param allPaths
     */
    void findAllPaths(Vertex *source, Vertex *destination, std::vector<Vertex *> &path,
                      std::vector<std::vector<Vertex *>> &allPaths);

    /**
     * find an edge in the graph, based on a a source and a destination vertices
     * @param source
     * @param destination
     * @return edge
     */
    Edge *findEdge(Vertex *source, Vertex *destination);

protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double **distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall



    bool isIn(std::string n, std::vector<std::string> vec);

    /**
     * delete a vertex from the graph, making a subgraph from a graph
     * @param name
     */
    void deleteVertex(std::string name);

    double getPathCost(const std::vector<Vertex *> &path);

    bool TSPUtil(Vertex *v, std::vector<Vertex *> &path, std::vector<Vertex *> &shortestPath, double &shortestPathCost,
                 int &numOfPossiblePaths);

    bool TSP(std::vector<Vertex *> &shortestPath, double &shortestPathCost);
};

void deleteMatrix(int **m, int n);

void deleteMatrix(double **m, int n);


#endif //PROJECT_2_GRAPH_H
