//
// Created by david on 5/8/23.
//

#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(long id) : id(id) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge *Vertex::addEdge(Vertex *d, double dist) {
    auto newEdge = new Edge(this, d, dist);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdge(long destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                } else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        } else {
            it++;
        }
    }
    return removedEdge;
}

Edge *Vertex::getEdge(long destID){

    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {

            return edge; // allows for multiple edges to connect the same pair of vertices (multigraph)
        } else {
            it++;
        }
    }
    return nullptr;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

long Vertex::getId() const {
    return this->id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


void Vertex::print() const {
    std::cout << "Vertex: " << id << std::endl;
    std::cout << "Adjacent to: ";
    for (const Edge *e: adj) {
        std::cout << e->getDest()->getId() << " ";
    }
    std::cout << std::endl;
    std::cout << "Visited: " << visited << std::endl;
    std::cout << "Distance: " << dist << std::endl;
    std::cout << "Path: " << path << std::endl;
}

void Vertex::eraseChildren() {
    children.clear();
}

void Vertex::addChildren(long s) {
    children.push_back(s);
}

std::vector<long> Vertex::getChildren() {
    return children;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double d) : orig(orig), dest(dest), distance(d) {}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->distance;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

double Vertex::getLatitude() {
    return latitude;
}

double Vertex::getLongitude() {
    return longitude;
}

void Vertex::setLatitude(double latitude_) {
    latitude=latitude_;
}

void Vertex::setLongitude(double longitude_) {
    longitude=longitude_;
}



