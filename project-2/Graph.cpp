#include <climits>
#include <queue>
#include "Graph.h"
#include <algorithm>
#include <unordered_set>

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
            std::cout << vertex->getId() << " -> " << edge->getDest()->getId() << " (distance: " << edge->getDistance()
                      << ")" << std::endl;
        }
    }
}


bool Graph::isIn(std::string n, std::vector<std::string> vec) {
    for (std::string s: vec) {
        if (s == n) return true;
    }
    return false;
}


void Graph::deleteVertex(std::string name) {
    auto v = findVertex(name);
    for (auto e: v->getAdj()) {
        auto s = e->getDest()->getId();
        v->removeEdge(s);
    }
    for (auto e: v->getIncoming()) {
        e->getOrig()->removeEdge(name);
    }
    auto it = vertexSet.begin();
    while (it != vertexSet.end()) {
        Vertex *currentVertex = *it;
        if (currentVertex->getId() == name) {
            it = vertexSet.erase(it);
        } else {
            it++;
        }
    }
}


/**
 * Function to check for pendant vertices in the graph
 * @return true if the graph has pendant vertices, false otherwise
 */
bool Graph::hasPendantVertex() {
    for (auto v: vertexSet)
        if (v->getAdj().size() == 1) {
            std::cout << "Graph has pendant vertex: " << v->getId() << std::endl;
            return true;
        }

    return false;
}


/**
 *
 * @param path
 * @return
 */
double Graph::getPathCost(const std::vector<Vertex *> &path) {
    double totalCost = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        for (auto edge: path[i]->getAdj()) {
            if (edge->getDest() == path[i + 1]) {
                totalCost += edge->getDistance();
                break;
            }
        }
    }
    return totalCost;
}

/**
 *
 * @param v
 * @param path
 * @param shortestPath
 * @param shortestPathCost
 * @param numOfPossiblePaths
 * @return
 */
bool
Graph::TSPUtil(Vertex *v, std::vector<Vertex *> &path, std::vector<Vertex *> &shortestPath, double &shortestPathCost,
               int &numOfPossiblePaths) {
    if (path.size() == vertexSet.size()) {
        for (auto edge: v->getAdj()) {
            if (edge->getDest() == path[0]) {
                path.push_back(path[0]);
                double pathCost = getPathCost(path);

                // Print path and its cost
                std::cout << "Path: ";
                for (auto vertex: path)
                    std::cout << vertex->getId() << " ";
                std::cout << "Cost: " << pathCost << std::endl;
                numOfPossiblePaths++;
                if (shortestPath.empty() || pathCost < shortestPathCost) {
                    shortestPath = path;
                    shortestPathCost = pathCost;
                }
                path.pop_back();
                return true;
            }
        }
        return false;
    }

    for (auto edge: v->getAdj()) {
        Vertex *w = edge->getDest();
        if (std::find(path.begin(), path.end(), w) != path.end())
            continue;
        path.push_back(w);
        TSPUtil(w, path, shortestPath, shortestPathCost, numOfPossiblePaths);
        path.pop_back();
    }

    return !shortestPath.empty();
}


/**
 * * Check if the graph has a Hamiltonian cycle.
 * (visit all nodes only once and return to the starting node)
 * If it has, return the minimum cost cycle.
 * conditions:
 * - graph must be connected
 * - graph must not have pendant vertices
 * - graph must not have articulation points
 * @param shortestPath
 * @param shortestPathCost
 * @return true if the graph has a Hamiltonian cycle, false otherwise
 */
bool Graph::TSP(std::vector<Vertex *> &shortestPath, double &shortestPathCost) {
    if (vertexSet.empty()) {
        std::cout << "Graph is empty" << std::endl;
        return false;
    }

    if (hasPendantVertex()) {
        std::cout << "Graph has a pendant vertex" << std::endl;
        return false;
    }

    int numOfPossiblePaths = 0;
    std::vector<Vertex *> path;
    path.push_back(vertexSet[0]); // Start from any vertex
    auto res = TSPUtil(vertexSet[0], path, shortestPath, shortestPathCost, numOfPossiblePaths);
    std::cout << "Number of possible paths: " << numOfPossiblePaths << std::endl;
    return res;
}

/**
 * Utility function to check if the graph has a Hamiltonian cycle.
 * @param v
 * @param path
 * @param pathCost
 * @return
 */
double Graph::hasHamiltonianCycleUtil(Vertex *v, std::vector<Vertex *> &path, double &pathCost) {
    if (path.size() == vertexSet.size()) {
        for (auto edge: v->getAdj()) {
            if (edge->getDest() == path[0]) {
                path.push_back(path[0]); // Closing the cycle
                pathCost = getPathCost(path);
                path.pop_back(); // Revert the cycle closing
                return true;  // found a Hamiltonian cycle
            }
        }
        return false;
    }

    for (auto edge: v->getAdj()) {
        Vertex *w = edge->getDest();
        if (std::find(path.begin(), path.end(), w) != path.end())
            continue;
        path.push_back(w);
        if (hasHamiltonianCycleUtil(w, path, pathCost))
            return true;  // propagate the success up the call stack
        path.pop_back();
    }

    return false;
}

/**
 * Check if the graph has a Hamiltonian cycle.
 * conditions:
 * - graph must be connected
 * - graph must not have pendant vertices
 * - graph must not have articulation points
 * @param path
 * @param pathCost
 * @return
 */
bool Graph::hasHamiltonianCycle(std::vector<Vertex *> &path, double &pathCost) {
    if (this->vertexSet.empty()) {
        std::cout << "Graph is empty" << std::endl;
        return false;
    }

    if (hasPendantVertex()) {
        std::cout << "Graph has a pendant vertex" << std::endl;
        return false;
    }


    path.push_back(this->vertexSet[0]);
    auto res = hasHamiltonianCycleUtil(this->vertexSet[0], path, pathCost);
    return res;
}


