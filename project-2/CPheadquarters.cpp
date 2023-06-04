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
        graph.addVertex(origin);
        graph.addVertex(destination);

        graph.addEdge(origin, destination, distance);
        graph.addEdge(destination, origin, distance);
    }
}


void CPheadquarters::read_establishments(string path){
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


        longitude_ = stod(temp1);
        latitude_ = stod(temp2);

        auto v = graph.findVertex(id_);
        v->setLongitude(longitude_);
        v->setLatitude(latitude_);

        // print information about the station, to make sure it was imported correctly
        //cout << "station: " << nome << " distrito: " << distrito << " municipality: " << municipality << " township: " << township << " line: " << line << endl;
    }
}


void CPheadquarters::heuristicRec(Vertex *v, string route[], unsigned int currentIndex, double distance, unsigned int &nodesVisited, double &totalDistance){

    bool nodesStillUnvisited = false;
    string id1 = v->getId();
    Establishment st1 = stations.find(id1)->second;

    double long1 = st1.get_longitude();
    double lat1 = st1.get_latitude();

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
            string id2 = edge->getDest()->getId();
            Establishment st2 = stations.find(id2)->second;

            double long2 = st2.get_longitude();
            double lat2 = st2.get_latitude();

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

void CPheadquarters::heuristic(string route[], unsigned int &nodesVisited, double &totalDistance, string id) {

    for (const auto &vertex: graph.getVertexSet()) {
        vertex->setVisited(false);

    }


    Vertex *actual = graph.findVertex(id);

    double distance = 0;
    route[0] = actual->getId();

    actual->setVisited(true);

    heuristicRec(actual, route, 1, distance, nodesVisited, totalDistance);
}


void CPheadquarters::chooseRoute(){
    string id;
    int pathSize = graph.getNumVertex();
    string path[pathSize];
    unsigned int nodesVisited = 0;
    double distance = 0;
    for(auto it =stations.begin(); it != stations.end(); it++){
        id = it->first;
        heuristic(path, nodesVisited, distance, id);
        if(nodesVisited == pathSize){
            string sourceId = path[pathSize-1];
            string destId = path[0];
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
    std::unordered_map<std::string,Vertex *> vertexis = graph.getVertexSet();
    for (auto v: vertexis) {
        v.second->setVisited(false);
        v.second->setDist(std::numeric_limits<double>::max());
        v.second->eraseChildren();
    }

    Vertex *root = graph.getVertexSet()[0];
    root->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(root);
    while (q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        v->getPath()->getOrig()->addChildren(v->getPath()->getOrig()->getId());
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
        result+= getDist(i,i+1);
    }

    cout<<"Result"<<result;

}

double CPheadquarters::getDist(int a,int b){
    for (auto edge: graph.findVertex(a)->getAdj()){
        if (edge->getDest()->getId()==b) return edge->getDist();
    }
    return haversineDistance(graph.findVertex(a)->getLatitude(),graph.findVertex(a)->getLon(), graph.findVertex(b)->getLat(), graph.findVertex(b)->getLon());
}

constexpr double kEarthRadiusKm = 6371.0;

double CPheadquarters::degreesToRadians (double degrees) {
    return degrees * M_PI / 180.0;
}

double CPheadquarters::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat=degreesToRadians(lat2-lat1);
    double dLon=degreesToRadians(lon2-lon1);
    double a =std::sin(dlat / 2) * std::sin(dLat / 2) +
                std::cos(degreesToRadians (lat1)) * std::cos(degreesToRadians (lat2)) *
             std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return kEarthRadiusKm * c;
}