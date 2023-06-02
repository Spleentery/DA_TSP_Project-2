#include <iostream>
#include "CPheadquarters.h"

using namespace std;

int main() {
    CPheadquarters CP;
    string path;
    cout<<"Insert path to file to construct graph (../network.csv): ";
    getline(cin, path);
    CP.read_network(path);
    cout<<"Insert path to file regarding stations (../stations.csv): ";
    getline(cin, path);
    cout<<endl;
    CP.read_stations(path);
    CP.getGraph().print();
    int n;
    cout << "\n-------------- An Analysis Tool for Railway Network Management --------------\n" << endl;
    do {
        cout << "\n1 - T2.1 Backtracking Algorithm\n";
        cout << "2 - T2.2 Triangular Approximation Heuristic\n";
        cout << "3 - T2.3 other heuristic algorithms\n";
        cout << "8 - Exit\n";


        bool validInput = false;

        while (!validInput) {
            cout << "Insert your option:\n";
            cin >> n;

            if (cin.fail() || n < 1 || n > 8) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 8." << endl;
            } else {
                validInput = true;
            }
        }

        switch (n) {
            case 1: {
                CP.backtrack();
                break;
            }

            case 2: {


            }

            case 3: {
                //CP.print3();
                CP.chooseRoute();

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