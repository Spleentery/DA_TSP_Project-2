//
// Created by david on 5/8/23.
//

#ifndef PROJECT_2_VERTEXEDGE_H
#define PROJECT_2_VERTEXEDGE_H


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>


class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(std::string id);

    bool operator<(Vertex &vertex) const; // // required by MutablePriorityQueue

    std::string getId() const;

    std::vector<Edge *> getAdj() const;

    bool isVisited() const;

    bool isAdded() const;

    bool isProcessing() const;

    unsigned int getIndegree() const;

    double getDist() const;

    Edge *getPath() const;

    std::vector<Edge *> getIncoming() const;

    void setId(int info);

    void setVisited(bool visited);

    void setAdded(bool added);

    void setProcesssing(bool processing);

    void setIndegree(unsigned int indegree);

    void setDist(double dist);

    void setPath(Edge *path);

    Edge *addEdge(Vertex *dest, double w);

    bool removeEdge(std::string destID);

    Edge *getEdge(std::string destID);


protected:
    std::string id;           // identifier
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool added = false;
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0;        // required by MutablePriorityQueue and UFDS
    void print() const;
};


/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double d);

    Vertex *getDest() const;

    double getDistance() const;

    bool isSelected() const;

    Vertex *getOrig() const;

    Edge *getReverse() const;

    double getFlow() const;

    void setSelected(bool selected);

    void setReverse(Edge *reverse);

    void setFlow(double flow);





protected:
    Vertex *dest; // destination vertex
    double distance; // edge weight, can also be used for capacity


    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};



#endif //PROJECT_2_VERTEXEDGE_H
