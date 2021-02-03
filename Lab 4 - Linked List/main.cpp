#include <iostream>
#include <fstream>
#include "LinkedList.h"
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
    
    string line, dataStr;
    int currentList = 0, dataInt;
    bool result;
    LinkedList<string> *stringList = new LinkedList<string>;
    LinkedList<int> *intList = new LinkedList<int>;
    
    while (in >> line) {
        out << line << " ";
        if (line == "INT" || line == "STRING") {
            currentList = line == "INT" ? 0 : 1;
            out << "true";
        } else {
            switch (currentList) {
                case 0:
                    if (line == "size") out << intList -> size();
                    else if (line == "printList") out << intList -> iterateList();
                    else if (line == "insertHead") {
                        in >> dataInt;
                        result = intList -> insertHead(dataInt);
                        out << dataInt << " " << (result ? "true" : "false");
                    }
                    else if (line == "insertTail") {
                        in >> dataInt;
                        result = intList -> insertTail(dataInt);
                        out << dataInt << " " << (result ? "true" : "false");
                    }
                    else if (line == "at") {
                        in >> dataInt;
                        out << dataInt << " ";
                        try {
                            out << intList -> at(dataInt) << " true";
                        } catch (char const *err) {
                            out << err;
                        }
                    }
                    else if (line == "remove") {
                        in >> dataInt;
                        result = intList -> remove(dataInt);
                        out << dataInt << " " << (result ? "true" : "false");
                    }
                    else if (line == "clear") {
                        result = intList -> clear();
                        out << (result ? "true" : "false");
                    }
                    else if (line == "insertAfter") {
                        int dataInt2;
                        in >> dataInt;
                        in.ignore(1);
                        in >> dataInt2;
                        result = intList -> insertAfter(dataInt, dataInt2);
                        out << dataInt << " " << dataInt2 << " " << (result ? "true" : "false");
                    }
                    else if (line == "iterateList") out << intList -> iterateList();
                    break;
                case 1:
                    if (line == "size") out << stringList -> size();
                    else if (line == "printList") out << stringList -> iterateList();
                    else if (line == "insertHead") {
                        in >> dataStr;
                        result = stringList -> insertHead(dataStr);
                        out << dataStr << " " << (result ? "true" : "false");
                    }
                    else if (line == "insertTail") {
                        in >> dataStr;
                        result = stringList -> insertTail(dataStr);
                        out << dataStr << " " << (result ? "true" : "false");
                    }
                    else if (line == "at") {
                        in >> dataInt;
                        out << dataInt << " ";
                        try {
                            out << stringList -> at(dataInt) << " true";
                        } catch (char const *err) {
                            out << err;
                        }
                    }
                    else if (line == "remove") {
                        in >> dataStr;
                        result = stringList -> remove(dataStr);
                        out << dataStr << " " << (result ? "true" : "false");
                    }
                    else if (line == "clear") {
                        result = stringList -> clear();
                        out << (result ? "true" : "false");
                    }
                    else if (line == "insertAfter") {
                        string dataStr2;
                        in >> dataStr;
                        in.ignore(1);
                        in >> dataStr2;
                        result = stringList -> insertAfter(dataStr, dataStr2);
                        out << dataStr << " " << dataStr2 << " " << (result ? "true" : "false");
                    }
                    else if (line == "iterateList") out << stringList -> iterateList();
            }
        }
        out << endl;
    }
    
    delete stringList;
    delete intList;
    return 0;
}
