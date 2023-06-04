#include <climits>
#include <queue>
#include "Graph.h"
#include <algorithm>
#include <unordered_set>
#include <chrono>

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_map<long,Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


Vertex *Graph:: findVertex(const long id) const {
    auto it = vertexSet.find(id);
    if(it!=vertexSet.end()){
        return it->second;
    }
    return nullptr;
}


bool Graph::addVertex(const long id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet[id]=(new Vertex(id));
    return true;
}


bool Graph::addEdge(const long sourc, const long dest, double d) {
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
        std::cout << vertex.second->getId() << " ";
    }
    std::cout << "\nEdges:\n";
    for (const auto &vertex: vertexSet) {
        for (const auto &edge: vertex.second->getAdj()) {
            std::cout << vertex.second->getId() << " -> " << edge->getDest()->getId() << " (distance: " << edge->getDistance()
                      << ")" << std::endl;
        }
    }
}


void Graph::deleteVertex(long name) {
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
        auto currentVertex = *it;
        if (currentVertex.second->getId() == name) {
            it = vertexSet.erase(it);
        } else {
            it++;
        }
    }
}



bool Graph::hasPendantVertex() {
    for (auto v: vertexSet)
        if (v.second->getAdj().size() == 1) {
            std::cout << "Graph has pendant vertex: " << v.second->getId() << std::endl;
            return true;
        }
    return false;
}



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


bool Graph::TSPUtil(Vertex *v, std::vector<Vertex *> &path, std::vector<Vertex *> &shortestPath, double &shortestPathCost,
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


bool Graph::TSP(std::vector<Vertex *> &shortestPath, double &shortestPathCost) {
    if (vertexSet.empty()) {
        std::cout << "Graph is empty" << std::endl;
        return false;
    }

    if (hasPendantVertex()) {
        std::cout << "Graph has a pendant vertex" << std::endl;
        return false;
    }

    if(hasArticulationPoint()){
        std::cout << "Graph has an articulation point" << std::endl;
        return false;
    }

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Calculating TSP using backtracking..." << std::endl;
    std::cout << "Please stand by..." << std::endl;

    // Measure execution time
    // ...

    int numOfPossiblePaths = 0;
    std::vector<Vertex *> path;
    path.push_back(vertexSet[0]); // Start from any vertex
    auto res = TSPUtil(vertexSet[0], path, shortestPath, shortestPathCost, numOfPossiblePaths);
    std::cout << "Number of possible paths: " << numOfPossiblePaths << std::endl;
    // End the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    return res;
}


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


bool Graph::hasHamiltonianCycle(std::vector<Vertex *> &path, double &pathCost) {

    if (this->vertexSet.empty()) {
        std::cout << "Graph is empty" << std::endl;
        return false;
    }

    if (hasPendantVertex()) {
        std::cout << "Graph has a pendant vertex" << std::endl;
        return false;
    }

    if(hasArticulationPoint()){
        std::cout << "Graph has an articulation point" << std::endl;
        return false;
    }

    // Start the timer
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Searching for a Hamiltonian Cycle..." << std::endl;
    std::cout << "Please stand by..." << std::endl;

    // Measure execution time
    // ...
    path.push_back(this->vertexSet[0]);
    auto res = hasHamiltonianCycleUtil(this->vertexSet[0], path, pathCost);

    // End the timer
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    return res;
}



bool Graph::hasArticulationPointUtil(Vertex* pCurrentVertex, int time) {
    int children = 0;
    long currentVertexIdInt = pCurrentVertex->getId();
    visited[currentVertexIdInt] = true;
    visited[currentVertexIdInt] = true;

    disc[currentVertexIdInt] = low[currentVertexIdInt] = ++time;

    for (auto edge : pCurrentVertex->getAdj()) {
        Vertex* pAdjacentVertex = edge->getDest();
        long adjacentVertexIdInt = pAdjacentVertex->getId();
        if (!visited[adjacentVertexIdInt]) {
            children++;
            parent[adjacentVertexIdInt] = currentVertexIdInt;

            if (hasArticulationPointUtil(pAdjacentVertex, time))
                return true;

            low[currentVertexIdInt] = std::min(low[currentVertexIdInt], low[adjacentVertexIdInt]);

            if (parent[currentVertexIdInt] == -1 && children > 1) {
                ap[currentVertexIdInt] = true;
                return true;
            }

            if (parent[currentVertexIdInt] != -1 && low[adjacentVertexIdInt] >= disc[currentVertexIdInt]) {
                ap[currentVertexIdInt] = true;
                return true;
            }
        }
        else if (adjacentVertexIdInt != parent[currentVertexIdInt]) {
            low[currentVertexIdInt] = std::min(low[currentVertexIdInt], disc[adjacentVertexIdInt]);
        }
    }

    return false;
}


bool Graph::hasArticulationPoint() {
    int V = vertexSet.size();
    disc.assign(V, -1);
    low.assign(V, -1);
    parent.assign(V, -1);
    visited.assign(V, false);
    ap.assign(V, false);

    for (auto vertex : vertexSet) {
        if (!visited[vertex.second->getId()]) {
            if (hasArticulationPointUtil(vertex.second, 0))
                return true;
        }
    }

    return false;
}


