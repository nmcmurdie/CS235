#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CR.h"
#include "CDH.h"
#include "CSG.h"
#include "SNAP.h"
using namespace std;

// Print all stored data in vectors: snaps, csgs, cdhs, & crs
void printVectors(ostream& out, vector<CR>& crs, vector<CDH>& cdhs, vector<CSG>& csgs, vector<SNAP>& snaps) {
    out << endl << "Vectors:" << endl;
    
    for (int i = 0; i < snaps.size(); i++) {
        out << snaps[i];
    }
    for (int i = 0; i < csgs.size(); i++) {
        out << csgs[i];
    }
    for (int i = 0; i < cdhs.size(); i++) {
        out << cdhs[i];
    }
    for (int i = 0; i < crs.size(); i++) {
        out << crs[i];
    }
}

// For each course grade: find student name then print that name with their grade
void printGrades(ostream& out, vector<CSG>& csgs, vector<SNAP>& snaps) {
    string className;
    out << endl << "Course Grades:" << endl;
    
    for (int i = 0; i < csgs.size(); i++) {
        if (i > 0 && csgs[i - 1].getClassName() != csgs[i].getClassName()) {
            out << endl;
        }
        
        const string ID = csgs[i].getID();
        string studentName;
        for (int j = 0; j < snaps.size(); j++) {
            if (ID == snaps[j].getID()) {
                studentName = snaps[j].getName();
                break;
            }
        }
        
        out << csgs[i].getClassName() << "," << studentName << "," << csgs[i].getGrade() << endl;
    }
}

// For each student: print student details & find all classes student is in and print the class: names, days, time, and room
void printSchedules(ostream& out, vector<CSG>& csgs, vector<CR>& crs, vector<CDH>& cdhs, vector<SNAP>& snaps) {
    out << endl << "Student Schedules:" << endl;
    
    for (int i = 0; i < snaps.size(); i++) {
        out << snaps[i].getName() << ", " << snaps[i].getID() << ", "
            << snaps[i].getTitle() << ", " << snaps[i].getPhoneNumber() << endl;
        
        for (int j = 0; j < csgs.size(); j++) {
            if (csgs[j].getID() == snaps[i].getID()) {
                string time, days = "", className = csgs[j].getClassName();
                out << "\t" << className << " ";
                
                for (int k = 0; k < cdhs.size(); k++) {
                    if (cdhs[k].getClassName() == className) {
                        days.append(cdhs[k].getDay());
                        time = cdhs[k].getTime();
                    }
                }
                out << days << " " << time;
                
                for (int k = 0; k < crs.size(); k++) {
                    if (crs[k].getClassName() == className) {
                        out << ", " << crs[k].getRoom() << endl;
                        break;
                    }
                }
            }
        }
        if (i + 1 != snaps.size()) {
            out << endl;
        }
    }
}

// Read files and construct data, then use appropriate functions to print out the data
int main(int argc, const char * argv[]) {
    // Storage Vectors
    vector<CR> crs;
    vector<CDH> cdhs;
    vector<CSG> csgs;
    vector<SNAP> snaps;
    
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
    
    // Read Data from Files
    out << "Input Strings:" << endl;
    for (string line; getline(in, line);) {
        string type, day, studentID, studentName, className, title, phoneNumber, invalid, time, room, grade;
        istringstream input (line);
        getline(input, type, '(');
        
        try {
            if (type == "snap") {
                getline(input, studentID, ',');
                getline(input, studentName, ',');
                getline(input, title, ',');
                getline(input, phoneNumber, ')');
                input.ignore(3);
                snaps.push_back(SNAP(studentID, studentName, title, phoneNumber));
            }
            else if (type == "csg") {
                getline(input, className, ',');
                getline(input, studentID, ',');
                getline(input, grade, ')');
                input.ignore(4);
                csgs.push_back(CSG(className, studentID, grade));
            }
            else if (type == "cdh") {
                getline(input, className, ',');
                getline(input, day, ',');
                getline(input, time, ')');
                input.ignore(3);
                cdhs.push_back(CDH(className, day, time));
            }
            else if (type == "cr") {
                getline(input, className, ',');
                getline(input, room, ')');
                input.ignore(3);
                crs.push_back(CR(className, room));
            }
            else {
                throw runtime_error("**Error: ");
            }
        }
        catch(exception& e) {
            out << e.what();
        }
        
        if (line.size() > 0) {
            out << line << endl;
        }
    }
    
    // Print Vectors, Grades, & Schedules
    printVectors(out, crs, cdhs, csgs, snaps);
    printGrades(out, csgs, snaps);
    printSchedules(out, csgs, crs, cdhs, snaps);
    return 0;
}
