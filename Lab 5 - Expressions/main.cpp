#include <iostream>
#include <fstream>
#include <sstream>
#include "ExpressionManager.h"
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
    
    ExpressionManager *expr = nullptr;
    // Read Input File
    for (string line; getline(in, line);) {
        string command, data;
        istringstream read(line);
        read >> command;
        try {
            if (command == "Expression:") {
                read.ignore(1);
                getline(read, data);
                if (expr != nullptr) delete expr;
                expr = new ExpressionManager(data);
                out << endl << command << " " << expr -> toString() << endl;
                continue;
            }
            
            out << command << " ";
            if (command == "Infix:") {
                out << expr -> infix();
            }
            else if (command == "Postfix:") {
                out << expr -> postfix();
            }
            else if (command == "Prefix:") {
                out << expr -> prefix();
            }
            else if (command == "Value:") {
                out << expr -> value();
            }
            out << endl;
        } catch (char const* err) {
            out << err << endl;
        }
    }
    if (expr != nullptr) delete expr;
    return 0;
}
