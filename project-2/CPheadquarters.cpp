//
// Created by david on 5/8/23.
//

#include <fstream>
#include <sstream>
#include "CPheadquarters.h"
#include <chrono>
#include <set>
#include <cmath>
#include <string>

using namespace std;

void CPheadquarters::read_network(string path){
    std::ifstream inputFile1(path);
    string line1;
    std::getline(inputFile1, line1); // ignore first line
    while (getline(inputFile1, line1, '\n')) {

        if (!line1.empty() && line1.back() == '\r') { // Check if the last character is '\r'
            line1.pop_back(); // Remove the '\r' character
        }

        string station_A;
        string station_B;
        string temp;
        int capacity;
        string service;

        stringstream inputString(line1);

        getline(inputString, station_A, ',');
        getline(inputString, station_B, ',');
        getline(inputString, temp, ',');
        getline(inputString, service, ',');

        capacity = stoi(temp);
        graph.addVertex(station_A);
        graph.addVertex(station_B);

        graph.addEdge(station_A, station_B, capacity);
    }
}

void CPheadquarters::read_stations(string path){
    std::ifstream inputFile2(R"(../stations.csv)");
    string line2;
    std::getline(inputFile2, line2); // ignore first line

    while (getline(inputFile2, line2, '\n')) {

        if (!line2.empty() && line2.back() == '\r') { // Check if the last character is '\r'
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

        longitude_ = stoi(temp1);
        latitude_ = stoi(temp2);


        Station station(id_, longitude_, latitude_);
        stations[id_] = station;

        // print information about the station, to make sure it was imported correctly
        //cout << "station: " << nome << " distrito: " << distrito << " municipality: " << municipality << " township: " << township << " line: " << line << endl;
    }
}

void CPheadquarters::read_files() {

    //--------------------------------------------Read network.csv--------------------------------------------
    std::ifstream inputFile1(R"(../network.csv)");
    string line1;
    std::getline(inputFile1, line1); // ignore first line
    while (getline(inputFile1, line1, '\n')) {

        if (!line1.empty() && line1.back() == '\r') { // Check if the last character is '\r'
            line1.pop_back(); // Remove the '\r' character
        }

        string station_A;
        string station_B;
        string temp;
        int capacity;
        string service;

        stringstream inputString(line1);

        getline(inputString, station_A, ',');
        getline(inputString, station_B, ',');
        getline(inputString, temp, ',');
        getline(inputString, service, ',');

        capacity = stoi(temp);
        graph.addVertex(station_A);
        graph.addVertex(station_B);

        graph.addEdge(station_A, station_B, capacity);
    }


    //--------------------------------------------Read stations.csv--------------------------------------------
    std::ifstream inputFile2(R"(../stations.csv)");
    string line2;
    std::getline(inputFile2, line2); // ignore first line

    while (getline(inputFile2, line2, '\n')) {

        if (!line1.empty() && line1.back() == '\r') { // Check if the last character is '\r'
            line1.pop_back(); // Remove the '\r' character
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

        longitude_ = stoi(temp1);
        latitude_ = stoi(temp2);


        Station station(id_, longitude_, latitude_);
        stations[id_] = station;

        // print information about the station, to make sure it was imported correctly
        //cout << "station: " << nome << " distrito: " << distrito << " municipality: " << municipality << " township: " << township << " line: " << line << endl;
    }
}

double CPheadquarters::heuristicRec(Vertex *v, string path[], unsigned int currentIndex, double distance){

    bool nodesStillUnvisited = false;
    string id1 = v->getId();
    Station st1 = stations.find(id1)->second;

    double long1 = st1.get_longitude();
    double lat1 = st1.get_latitude();

    Vertex *small;
    double smallAngle;
    double x;
    double y;
    double angle;
    double dist;

    for (const auto &edge: v->getAdj()) {
        Vertex *v2 = edge->getDest();
        double dist2 = edge->getWeight();
        if(v2->isVisited() == false){
            nodesStillUnvisited = true;
            string id2 = edge->getDest()->getId();
            Station st2 = stations.find(id1)->second;

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

    if(nodesStillUnvisited){
        path[currentIndex] = small->getId();
        small->setVisited(true);
        heuristicRec(small, path, currentIndex + 1, distance + dist);
    }
    else{
        return distance;
    }



}

double CPheadquarters::heuristic(string path[]) {

    for (const auto &vertex: graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    int pathSize = graph.getNumVertex() +1;
    path[pathSize];

    string first_id = stations.begin()->first;
    Vertex *actual = graph.findVertex(first_id);

    path[0] = actual->getId();
    path[pathSize] = actual->getId();
    actual->setVisited(true);

    double distance = 0;

    return heuristicRec(actual, path, 1, distance);


}

void CPheadquarters::print3(){
    int pathSize = graph.getNumVertex() +1;
    string path[pathSize];

    for(int i = 0; i < pathSize; i++){
        cout << path[i] << "->" <<endl;
    }

}


Graph CPheadquarters::getGraph() const {
    return this->graph;
}
