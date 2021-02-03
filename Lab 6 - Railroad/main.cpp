#include <iostream>
#include <fstream>
#include <sstream>
#include "Station.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // Open Files
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in)  {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    ofstream out(argv[2]);
    
    Station<int> station;

    // Parse Input File
    for (string line; getline(in, line);) {
        istringstream read(line);
        if (line.size() <= 1) continue;
        string command, dest, results;
        int car;
        getline(read, command, ':');
        out << command << ":";

        if (command == "Add") {
            read >> dest;
            out << dest;
            
            if (dest == "station") {
                read >> car;
                out << " " << car;
                results = station.addCar(car);
            }
            if (dest == "queue") results = station.addQueue();
            else if (dest == "stack") results = station.addStack();
            
            out << " " << results;
        }
        else if (command == "Remove") {
            read >> dest;
            
            if (dest == "station") results = station.removeCar();
            else if (dest == "queue") results = station.removeQueue();
            else if (dest == "stack") results = station.removeStack();
            out << dest << " " << results;
        }
        else if (command == "Top") {
            read >> dest;
            
            if (dest == "station") results = station.topCar();
            else if (dest == "queue") results = station.topQueue();
            else if (dest == "stack") results = station.topStack();
            out << dest << " " << results;
        }
        else if (command == "Size") {
            read >> dest;
            
            if (dest == "queue") results = station.sizeQueue();
            else if (dest == "stack") results = station.sizeStack();
            out << dest << " " << results;
        }
        else if (command == "Train") {
            out << " " << station.toString();
        }
        else if (command == "Find") {
            read >> car;
            out << car << " " << station.find(car);
        }
        out << endl;
    }
    
    return 0;
}
