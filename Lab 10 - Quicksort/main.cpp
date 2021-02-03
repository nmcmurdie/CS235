#include <iostream>
#include <fstream>
#include <sstream>
#include "QuickSort.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // Open Files
    if (argc < 3) return 1;
    ifstream in(argv[1]);
    
    if (!in)  return 2;
    ofstream out(argv[2]);
    
    // QuickSort instance
    QuickSort<int> sort;
    
    // Parse Input File
    for (string line, command; getline(in, line); out << endl) {
        if (line.size() < 1) continue;
        istringstream read(line);

        string data;
        read >> command;
        if (!read.eof()) read >> data;
        out << command << " " << (data.empty() ? "" : data);

        if (command == "QuickSort") {
            sort.createArray(stoi(data));
            out << " OK";
        }
        else if (command == "AddToArray") {
            sort.addElement(stoi(data));
            for (int i; read >> i;) {
                sort.addElement(i);
                out << "," << i;
            }
            out << " OK";
        }
        else if (command == "MedianOfThree") {
            int right;
            read >> right;
            out << "," << right << " = ";
            out << sort.medianOfThree(stoi(data), right);
        }
        else if (command == "Partition") {
            int right, pivot;
            read >> right >> pivot;
            out << "," << right << "," << pivot << " = ";
            out << sort.partition(stoi(data), right, pivot);
        }
        else if (command == "SortAll") {
            sort.clearStats();
            sort.sortAll();
            out << "OK";
        }
        else if (command == "Sort") {
            sort.clearStats();
            int right;
            read >> right;
            sort.sort(stoi(data), right);
            out << "," << right << " OK";
        }
        else if (command == "Stats") {
            out << sort.numComparisons() << "," << sort.numExchanges();
        }
        else if (command == "PrintArray") out << sort;
        else if (command == "Capacity") out << sort.capacity();
        else if (command == "Size") out << sort.size();
        else if (command == "Clear") out << (sort.clear() ? "OK" : "Error");
        else out << "NOT IMPLEMENTED";
    }
    
    return 0;
}
