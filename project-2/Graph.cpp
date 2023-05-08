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


bool Graph::addEdge(const std::string &sourc, const std::string &dest, int w, const std::string &service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);

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
            std::cout << vertex->getId() << " -> " << edge->getDest()->getId() << " (weight: " << edge->getWeight() << ", service: " << edge->getService() << ")" << std::endl;
        }
    }
}

// --------------------------------- Edmonds-Karp ---------------------------------


void Graph::testAndVisit(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}



bool Graph::findAugmentingPath(const std::string &s, const std::string &t) {
    Vertex *source = findVertex(s);
    Vertex *target = findVertex(t);
    if (source == nullptr || target == nullptr) {
        return false;
    }
    for (auto v: vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }
    source->setVisited(true);
    std::queue<Vertex *> q;
    q.push(source);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            double residual = e->getWeight() - e->getFlow();
            testAndVisit(q, e, w, residual);
        }
        for (auto e: v->getIncoming()) {
            auto w = e->getDest();
            double residual = e->getFlow();
            testAndVisit(q, e->getReverse(), w, residual);
        }
        if (target->isVisited()) {
            return true;
        }
    }
    return false;
}


int Graph::findMinResidual(Vertex *s, Vertex *t) {
    double minResidual = INT_MAX;
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            minResidual = std::min(minResidual, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            minResidual = std::min(minResidual, e->getFlow());
            v = e->getDest();
        }
    }
    return minResidual;
}


void Graph::updateFlow(Vertex *s, Vertex *t, int bottleneck) {
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + bottleneck);
            v = e->getOrig();
        } else {
            e->setFlow(flow - bottleneck);
            v = e->getDest();
        }
    }
}


int Graph::edmondsKarp(const std::string &s, const std::string &t) {
    for (auto e: vertexSet) {
        for (auto i: e->getAdj()) {
            i->setFlow(0);
        }
    }
    int maxFlow = 0;
    while (findAugmentingPath(s, t)) {
        int bottleneck = findMinResidual(findVertex(s), findVertex(t));
        updateFlow(findVertex(s), findVertex(t), bottleneck);
        maxFlow += bottleneck;
    }
    return maxFlow;
}

std::vector<std::string> Graph::find_sources(std::vector<std::string> desired_stations) {
    std::vector<std::string> res;

    for (std::string s: desired_stations) {
        bool flag = true;
        auto v = findVertex(s);
        if (v == nullptr) {
            std::cout << "Trouble finding source " << s << '\n';
            continue;
        }
        for (auto e: v->getIncoming()) {
            if (isIn(e->getOrig()->getId(), desired_stations)) {
                flag=false;
            }
        }
        if (flag) res.push_back(s);
    }
    return res;
}

std::vector<std::string> Graph::find_targets(std::vector<std::string> desired_stations) {
    std::vector<std::string> res;
    for (std::string s: desired_stations) {
        bool flag = true;
        auto v = findVertex(s);
        if (v == nullptr) {
            std::cout << "Trouble finding target " << s << '\n';
            continue;
        }
        for (auto e: v->getAdj()) {
            if (isIn(e->getDest()->getId(), desired_stations)) {
                flag=false;
            }
        }
        if (flag) res.push_back(s);
    }
    return res;
}


bool Graph::isIn(std::string n, std::vector<std::string> vec) {
    for (std::string s: vec) {
        if (s == n) return true;
    }
    return false;
}


int Graph::mul_edmondsKarp(std::vector<std::string> souces, std::vector<std::string> targets) {
    auto it1 = souces.begin();
    while (it1 != souces.end()) {
        if (isIn(*it1, targets)) {
            it1 = souces.erase(it1);
        } else it1++;
    }

    auto it2 = targets.begin();
    while (it2 != targets.end()) {
        if (isIn(*it2, souces)) {
            it2 = souces.erase(it2);
        } else it2++;
    }

    addVertex("temp_source");
    for (std::string s: souces) {
        addEdge("temp_source", s, INT32_MAX, "STANDARD");
    }

    addVertex("temp_targets");
    for (std::string s: targets) {
        addEdge(s, "temp_targets", INT32_MAX, "STANDARD");
    }
    for (auto e: vertexSet) {
        for (auto i: e->getAdj()) {
            i->setFlow(0);
        }
    }
    int maxFlow = 0;
    while (findAugmentingPath("temp_source", "temp_targets")) {
        int bottleneck = findMinResidual(findVertex("temp_source"), findVertex("temp_targets"));
        updateFlow(findVertex("temp_source"), findVertex("temp_targets"), bottleneck);
        maxFlow += bottleneck;
    }
    deleteVertex("temp_targets");
    deleteVertex("temp_source");
    return maxFlow;
}

// --------------------------------- Find ALL existing augmenting paths ---------------------------------


void Graph::findAllPaths(Vertex *source, Vertex *destination, std::vector<Vertex *> &path,
                         std::vector<std::vector<Vertex *>> &allPaths) {
    path.push_back(source);
    source->setVisited(true);

    if (source == destination) {
        allPaths.push_back(path);
    } else {
        for (auto edge: source->getAdj()) {
            Vertex *adjacent = edge->getDest();
            if (!adjacent->isVisited()) {
                findAllPaths(adjacent, destination, path, allPaths);
            }
        }
    }

    path.pop_back();
    source->setVisited(false);
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

