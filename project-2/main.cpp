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
            "\ne.g"
            "\n|Toy Graphs           |: ../Toy-Graphs/Toy-Graphs/shipping.csv"
            "\n|Real World Graphs    |: ../Real-world Graphs/Real-world Graphs/graph1/edges.csv"
            "\n|Extra Fully Connected|: ../Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv )"
            "\n:";
    getline(cin, path);
    CP.read_edges(path);
    cout<<"If necessary, insert path to file that contains latitude and longitude"
          "\n(e.g ../Real-world Graphs/Real-world Graphs/graph1/nodes.csv)"
          "\n Otherwise, press enter."
          "\n:";
    getline(cin, path);
    cout<<endl;
    if (!path.empty()) {
        CP.read_coordinates(path);
    }
    //CP.getGraph().print();
    int n;
    cout << "\n-------------- An Analysis Tool for Railway Network Management --------------\n" << endl;
    do {
        cout << "\n1 - T2.1 Backtracking Algorithm\n";
        cout << "2 - T2.2 Triangular Approximation Heuristic\n";
        cout << "3 - T2.3 Third Heuristic Algorithm\n";
        cout << "4 - T2.3 Forth Heuristic Algorithm\n";
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
                auto start_time = std::chrono::high_resolution_clock::now();

                CP.triangular_Approximation_Heuristic();

                auto end_time = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

                std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

                break;
            }

            case 3: {

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

            case 4: {

                //CP.print3();
                auto start_time = std::chrono::high_resolution_clock::now();


                CP.raquel();

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