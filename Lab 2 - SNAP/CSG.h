#ifndef CSG_h
#define CSG_h

#include <stdio.h>
#include "CourseInfo.h"

class CSG : public CourseInfo {
    private:
        std::string studentID = "";
        std::string studentGrade = "C";
        // Print class, called by << operator
        virtual std::string toString() const {
            std::ostringstream out;
            out << "csg" << CourseInfo::toString() << studentID << "," << studentGrade << ")";
            return out.str();
        }
    public:
        CSG(std::string className = "", std::string studentID = "", std::string studentGrade = "") :
            CourseInfo(className), studentID (studentID), studentGrade(studentGrade) {}
        // Get Student ID
        std::string getID() const {
            return this -> studentID;
        }
        // Get Student Grade
        std::string getGrade() const {
            return this -> studentGrade;
        }
};

#endif
