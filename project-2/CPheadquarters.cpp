//
// Created by david on 5/8/23.
//

#include <fstream>
#include <sstream>
#include "CPheadquarters.h"
#include "MutablePriorityQueue.h"
#include <chrono>
#include <set>
#include <cmath>
#include <string>

using namespace std;

void CPheadquarters::read_edges(string path){
    std::ifstream inputFile1(path);
    string line1;
    std::getline(inputFile1, line1); // ignore first line
    while (getline(inputFile1, line1, '\n')) {

        if (!line1.empty() && line1.back() == '\r') { // Check if the last character is '\r'
            line1.pop_back(); // Remove the '\r' character
        }

        string origin;
        string destination;
        string temp;
        double distance;


        stringstream inputString(line1);

        getline(inputString, origin, ',');
        getline(inputString, destination, ',');
        getline(inputString, temp, ',');


        distance = stod(temp);

        long origin_id = std::stol(origin);
        graph.addVertex(origin_id);

        long destination_id = std::stol(destination);
        graph.addVertex(destination_id);

        graph.addEdge(origin_id, destination_id, distance);
        graph.addEdge(destination_id, origin_id, distance);
        cout << origin << '\n';
    }
}


void CPheadquarters::read_coordinates(string path){
    std::ifstream inputFile2(path);
    string line2;
    std::getline(inputFile2, line2); // ignore first line


    while (getline(inputFile2, line2, '\n')) {

        if (!line2.empty() && line2.back() == '\n') { // Check if the last character is '\r'
            line2.pop_back(); // Remove the '\r' character
        }

        string id_;
        string temp1;
        string temp2;
        double longitude_;
        double latitude_;

        stringstream inputString(line2);

        getline(inputString, id_, ',');
        getline(inputString, temp1, ',');
        getline(inputString, temp2, ',');

        long long_id = std::stol(id_);
        longitude_ = stod(temp1);
        latitude_ = stod(temp2);

        auto v = graph.findVertex(long_id);
        v->setLongitude(longitude_);
        v->setLatitude(latitude_);

        cout << long_id << '\n';
    }
}


void CPheadquarters::heuristicRec(Vertex *v, long route[], unsigned int currentIndex, double distance, unsigned int &nodesVisited, double &totalDistance){

    bool nodesStillUnvisited = false;

    double long1 = v->getLongitude();
    double lat1 = v->getLatitude();

    Vertex *small;
    double smallAngle = 10000;
    double x;
    double y;
    double angle;
    double dist;

    for (const auto &edge: v->getAdj()) {
        Vertex *v2 = edge->getDest();
        double dist2 = edge->getDistance();
        if(v2->isVisited() == false){
            nodesStillUnvisited = true;

            double long2 = edge->getDest()->getLongitude();
            double lat2 = edge->getDest()->getLatitude();

            x = long1 - long2;
            y = lat1 - lat2;

            angle = atan2(y,x);

            if(angle < smallAngle){
                smallAngle = angle;
                small = v2;
                dist = dist2;
            }

        }
    }

    bool inRoute = false;
    for(int i = 0; i < currentIndex; i++){
        if(route[i] == v->getId()){
            inRoute = true;
        }
    }

    if(nodesStillUnvisited){
        route[currentIndex] = small->getId();
        small->setVisited(true);

        heuristicRec(small, route, currentIndex+1, distance + dist, nodesVisited, totalDistance);
    }
    else{
        nodesVisited = currentIndex;
        totalDistance = distance;

    }


}

void CPheadquarters::heuristic(long route[], unsigned int &nodesVisited, double &totalDistance, long id) {

    for (const auto vertex: graph.getVertexSet()) {
        vertex.second->setVisited(false);

    }


    Vertex *actual = graph.findVertex(id);

    double distance = 0;
    route[0] = actual->getId();

    actual->setVisited(true);

    heuristicRec(actual, route, 1, distance, nodesVisited, totalDistance);
}


void CPheadquarters::chooseRoute(){
    long id;
    auto pathSize = graph.getNumVertex();
    auto vertixes = graph.getVertexSet();
    long path[pathSize];
    unsigned int nodesVisited = 0;
    double distance = 0;
    for(auto it =vertixes.begin(); it != vertixes.end(); it++){
        id = it->first;
        heuristic(path, nodesVisited, distance, id);
        if(nodesVisited == pathSize){
            long sourceId = path[pathSize-1];
            long destId = path[0];
            Vertex *sourceV = graph.findVertex(sourceId);
            Edge *missingEdge = sourceV->getEdge(destId);
            if(missingEdge!= nullptr){
                distance += missingEdge->getDistance();
                for(int i = 0; i < pathSize; i++){
                    cout << path[i] << "->";
                }
                cout << destId;
                cout << "\nTotal distance: " << distance << endl;
                break;
            }
        }
    }
}



Graph CPheadquarters::getGraph() const {
    return this->graph;
}



void CPheadquarters::backtrack() {
    std::vector<Vertex*> shortestPath;
    double shortestPathCost = 0;


    if (this->graph.TSP(shortestPath, shortestPathCost)) {
        cout << "Shortest Hamiltonian cycle: ";
        for (auto vertex : shortestPath)
            cout << vertex->getId() << " ";
        cout << "\nCost: " << shortestPathCost << endl;
    }
    else {
        cout << "The graph does not have a Hamiltonian cycle" << endl;
    }
}

void CPheadquarters::hamiltonianCycle() {
    std::vector<Vertex*> path;
    double cost = 0;
    if (this->graph.hasHamiltonianCycle(path, cost)) {
        cout << "Hamiltonian cycle: ";
        for (auto vertex : path)
            cout << vertex->getId() << " ";
        cout << "\nCost: " << cost << endl;
    }
    else {
        cout << "The graph does not have a Hamiltonian cycle" << endl;
    }
}
void CPheadquarters::pathRec(Vertex* vertex){
    mst_preorder_path.push_back(vertex->getId());
    for (auto child : vertex->getChildren()) {
        pathRec(graph.getVertexSet()[child]);
    }
    return;
}


void CPheadquarters::triangular_Approximation_Heuristic() {
    std::unordered_map<long,Vertex *> vertexis = graph.getVertexSet();
    for (auto v: vertexis) {
        v.second->setVisited(false);
        v.second->setDist(std::numeric_limits<double>::max());
        v.second->eraseChildren();
    }

    Vertex *root = graph.findVertex(0);
    root->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(root);
    while (!q.empty()) {
        auto v = q.extractMin();
        cout<<"working on:"<<v->getId()<<'\n';
        v->setVisited(true);
        if(v->getId()!=0) {
            v->getPath()->getOrig()->addChildren(v->getId());
        }
        for (auto &e: v->getAdj()) {
            Vertex *w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if (e->getDistance() < oldDist) {
                    w->setDist(e->getDistance());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    mst_preorder_path.clear();
    pathRec(root);

    double result=0;

    for (int i = 0; i < mst_preorder_path.size()-1; i++) {
        result+= getDist(mst_preorder_path[i],mst_preorder_path[i+1]);
    }
    result+=getDist(mst_preorder_path[mst_preorder_path.size()-1],mst_preorder_path[0]);

    cout<<"Result:"<<result;

}

constexpr double EarthRadius = 6371.0;

double CPheadquarters::getDist(int a,int b){
    for (auto edge: graph.findVertex(a)->getAdj()){
        if (edge->getDest()->getId()==b) return edge->getDistance();
    }
    return haversineDistance(graph.findVertex(a)->getLatitude(),graph.findVertex(a)->getLongitude(), graph.findVertex(b)->getLatitude(), graph.findVertex(b)->getLongitude());
}



double CPheadquarters::degToRad (double degrees) {
    return degrees*M_PI/180.0;
}

double CPheadquarters::haversineDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double ang_lat=degToRad(latitude2-latitude1);
    double ang_lon=degToRad(longitude2-longitude1);
    double a =sin(ang_lat / 2) * sin(ang_lat / 2) +
            cos(degToRad (latitude1)) * cos(degToRad (latitude2)) *
             sin(ang_lon / 2) * sin(ang_lon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EarthRadius * c;
}