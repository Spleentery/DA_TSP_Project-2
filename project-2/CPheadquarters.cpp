//
// Created by david on 5/8/23.
//

#include <fstream>
#include <sstream>
#include "CPheadquarters.h"
#include <chrono>
#include <set>

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

        graph.addEdge(station_A, station_B, capacity, service);
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

        string nome;
        string distrito;
        string municipality;
        string township;
        string line;

        stringstream inputString(line2);

        getline(inputString, nome, ',');
        getline(inputString, distrito, ',');
        getline(inputString, municipality, ',');
        getline(inputString, township, ',');
        getline(inputString, line, ',');

        Station station(nome, distrito, municipality, township, line);
        stations[nome] = station;

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

        graph.addEdge(station_A, station_B, capacity, service);
    }


    //--------------------------------------------Read stations.csv--------------------------------------------
    std::ifstream inputFile2(R"(../stations.csv)");
    string line2;
    std::getline(inputFile2, line2); // ignore first line

    while (getline(inputFile2, line2, '\n')) {

        if (!line1.empty() && line1.back() == '\r') { // Check if the last character is '\r'
            line1.pop_back(); // Remove the '\r' character
        }

        string nome;
        string distrito;
        string municipality;
        string township;
        string line;

        stringstream inputString(line2);

        getline(inputString, nome, ',');
        getline(inputString, distrito, ',');
        getline(inputString, municipality, ',');
        getline(inputString, township, ',');
        getline(inputString, line, ',');

        Station station(nome, distrito, municipality, township, line);
        stations[nome] = station;

        // print information about the station, to make sure it was imported correctly
        //cout << "station: " << nome << " distrito: " << distrito << " municipality: " << municipality << " township: " << township << " line: " << line << endl;
    }
}


Graph CPheadquarters::getGraph() const {
    return this->graph;
}
