#include <iostream>
#include <fstream>
#include <sstream>
#include "AVL.h"
using namespace std;

int main(int argc, const char* argv[]) {
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
    
    // Create BSTs to be used later, set cout to print true/false instead of 1/0
    AVL<int> treeInt = AVL<int>();
    AVL<string> treeString = AVL<string>();
    int treeSelect = 0;
    out << boolalpha;
//    for (int i = 0; i < 10; ++i) treeInt.insertNode(i);
//    cout << treeInt << endl;
//    treeInt.removeNode(2);
//    cout << treeInt << endl;
    
    // Read in data
    for (string line; getline(in, line);) {
        istringstream read(line);
        string command;
        read >> command;
        out << command;
        
        // Process command with treeSelect (INT = 0, STRING = 1)
        if (command == "INT") {
            treeSelect = 0;
            out << " " << true;
        }
        else if (command == "STRING") {
            treeSelect = 1;
            out << " " << true;
        }
        else if (command == "add" && treeSelect) {
            string data;
            read >> data;
            bool result = treeString.insertNode(data);
            out << " " << data << " " << result;
        }
        else if (command == "add") {
            int data;
            read >> data;
            bool result = treeInt.insertNode(data);
            out << " " << data << " " << result;
        }
        else if (command == "remove" && treeSelect) {
            string data;
            read >> data;
            bool result = treeString.removeNode(data);
            out << " " << data << " " << result;
        }
        else if (command == "remove") {
            int data;
            read >> data;
            bool result = treeInt.removeNode(data);
            out << " " << data << " " << result;
        }
        else if (command == "find" && treeSelect) {
            string data;
            read >> data;
            string result = treeString.findNode(data) ? "found" : "not found";
            out << " " << data << " " << result;
        }
        else if (command == "find") {
            int data;
            read >> data;
            string result = treeInt.findNode(data) ? "found" : "not found";
            out << " " << data << " " << result;
        }
        else if (command == "print" && treeSelect) out << ":" << treeString;
        else if (command == "print") out << ":" << treeInt;
        else if (command == "size" && treeSelect) out << " " << treeString.getSize();
        else if (command == "size") out << " " << treeInt.getSize();
        else if (command == "clear" && treeSelect) out << " " << treeString.clearTree();
        else if (command == "clear") out << " " << treeInt.clearTree();
        out << endl;
    }
    
    return 0;
}

