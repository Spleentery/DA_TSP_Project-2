#include <iostream>
#include <chrono>
#include "CPheadquarters.h"

using namespace std;

int getValidInput(int lowerLimit, int upperLimit) {
    int n;
    bool validInput = false;
    while (!validInput) {
        cout << "Insert your option:\n";
        cin >> n;

        if (cin.fail() || n < lowerLimit || n > upperLimit) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << lowerLimit << " and " << upperLimit << "." << endl;
        } else {
            validInput = true;
        }
    }
    return n;
}

int main() {
    CPheadquarters CP;
    string path;
    cout << "Insert path to file to construct a graph "
            "\ne.g Toy Graphs: \n../Toy-Graphs/Toy-Graphs/shipping.csv or ../Toy-Graphs/Toy-Graphs/stadiums.csv or ../Toy-Graphs/Toy-Graphs/tourism.csv "
            "\nReal World Graphs: \n../Real-world Graphs/Real-world Graphs/graph1/edges.csv or ../Real-world Graphs/Real-world Graphs/graph2/edges.csv or ../Real-world Graphs/Real-world Graphs/graph3/edges.csv"
            "\nExtra Fully Connected: \n../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv ): ";
    getline(cin, path);
    CP.read_edges(path);
    cout<<"If necessary, insert path to file that contains latitude and longitude (e.g ../Real-world Graphs/Real-world Graphs/graph1/nodes.csv)"
          "\n otherwise, press enter ";
    getline(cin, path);
    cout<<endl;
    if (!path.empty()) {
        CP.read_establishments(path);
    }
    //CP.getGraph().print();
    int n;
    cout << "\n-------------- An Analysis Tool for Railway Network Management --------------\n" << endl;
    do {
        cout << "\n1 - T2.1 Backtracking Algorithm\n";
        cout << "2 - T2.2 Triangular Approximation Heuristic\n";
        cout << "3 - T2.3 other heuristic algorithms\n";
        cout << "8 - Exit\n";


        n = getValidInput(1, 8);

        switch (n) {
            case 1: {
                cout << "1 - TSP using Backtracking algorithm (for small graphs)\n";
                cout << "2 - Just find ANY the Hamiltonian Cycle (for big graphs)\n";
                int backtrack_choice;
                backtrack_choice = getValidInput(1, 2);
                switch(backtrack_choice){
                    case 1:
                        CP.backtrack();
                        break;

                    case 2:
                        CP.hamiltonianCycle();
                        break;

                    default: {
                        cerr << "Error: Invalid option selected." << endl;
                        break;
                    }
                }
                break;
            }

            case 2: {


            }

            case 3: {

                //CP.print3();
                auto start_time = std::chrono::high_resolution_clock::now();


                CP.chooseRoute();

// Code block to measure goes here

// End the timer
                auto end_time = std::chrono::high_resolution_clock::now();

// Compute the duration
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

// Print the duration
                std::cout << "Time taken: " << duration.count() << " ms" << std::endl;


                break;
            }

            case 8: {
                cout << "Exiting program..." << endl;
                break;
            }

            default: {
                cerr << "Error: Invalid option selected." << endl;
                break;
            }
        }
    } while (n != 8);

    return 0;
}