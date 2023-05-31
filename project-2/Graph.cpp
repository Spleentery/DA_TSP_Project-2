#include <climits>
#include <queue>
#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


Vertex *Graph::findVertex(const std::string &id) const {
    for (auto v: vertexSet) {
        if (v->getId() == id)
            return v;
    }
    return nullptr;
}







bool Graph::addVertex(const std::string &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}


bool Graph::addEdge(const std::string &sourc, const std::string &dest, double d) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, d);

    return true;
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}



void Graph::print() const {
    std::cout << "---------------- Graph----------------\n";
    std::cout << "Number of vertices: " << vertexSet.size() << std::endl;
    std::cout << "Vertices:\n";
    for (const auto &vertex: vertexSet) {
        std::cout << vertex->getId() << " ";
    }
    std::cout << "\nEdges:\n";
    for (const auto &vertex: vertexSet) {
        for (const auto &edge: vertex->getAdj()) {
            std::cout << vertex->getId() << " -> " << edge->getDest()->getId() << " (distance: " << edge->getDistance() << ")" << std::endl;
        }
    }
}




bool Graph::isIn(std::string n, std::vector<std::string> vec) {
    for (std::string s: vec) {
        if (s == n) return true;
    }
    return false;
}

Edge *Graph::findEdge(Vertex *source, Vertex *destination) {

    for (auto edge: source->getAdj()) {
        if (edge->getDest() == destination) {
            return edge;
        }
    }
    return nullptr;
}


std::vector<std::string> Graph::getSources() {
    std::vector<std::string> res;
    for (auto v : vertexSet) {
        if(v->getIncoming().empty()){
            res.push_back(v->getId());
        }
    }
    return res;
}

std::vector<std::string> Graph::getTargets() {
    std::vector<std::string> res;
    for (auto v : vertexSet) {
        if(v->getAdj().empty()){
            res.push_back(v->getId());
        }
    }
    return res;
}


void Graph::deleteVertex(std::string name) {
    auto v = findVertex(name);
    for(auto e : v->getAdj()){
        auto s = e->getDest()->getId();
        v->removeEdge(s);
    }
    for(auto e : v->getIncoming()){
        e->getOrig()->removeEdge(name);
    }
    auto it = vertexSet.begin();
    while (it!=vertexSet.end()){
        Vertex* currentVertex = *it;
        if(currentVertex->getId()==name){
            it=vertexSet.erase(it);
        }
        else{
            it++;
        }
    }
}

