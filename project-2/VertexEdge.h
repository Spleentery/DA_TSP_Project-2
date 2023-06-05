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
    Vertex(long id);

    bool operator<(Vertex &vertex) const; // // required by MutablePriorityQueue

    long getId() const;

    std::vector<Edge *> getAdj() const;

    bool isVisited() const;

    double getDist() const;

    Edge *getPath() const;

    std::vector<Edge *> getIncoming() const;

    void setId(int info);

    void setVisited(bool visited);

    void setDist(double dist);

    void setPath(Edge *path);

    Edge *addEdge(Vertex *dest, double w);

    bool removeEdge(long destID);

    Edge *getEdge(long destID);

    void eraseChildren();

    void addChildren(long s);

    std::vector<long> getChildren();

    double getLatitude();

    double getLongitude();

    void setLatitude(double latitude);

    void setLongitude(double longitude);

    int queueIndex = 0;
protected:
    long id;           // identifier
    std::vector<Edge *> adj;  // outgoing edges
    std::vector<long> children;

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    double longitude=0;
    double latitude=0;


    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    // required by MutablePriorityQueue and UFDS
    void print() const;

};


/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double d);

    Vertex *getDest() const;

    double getDistance() const;

    Vertex *getOrig() const;

protected:
    Vertex *dest; // destination vertex
    double distance; // edge weight, can also be used for capacity

    // used for bidirectional edges
    Vertex *orig;

};



#endif //PROJECT_2_VERTEXEDGE_H
