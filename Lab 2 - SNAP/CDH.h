#ifndef CDH_h
#define CDH_h

#include <stdio.h>
#include "CourseInfo.h"

class CDH : public CourseInfo {
    private:
        std::string day = "";
        std::string time = "";
        // Print class, called by << operator
        virtual std::string toString() const {
            std::ostringstream out;
            out << "cdh" << CourseInfo::toString() << day << "," << time << ")";
            return out.str();
        }
    public:
        CDH(std::string className = "", std::string day = "", std::string time = "") : CourseInfo(className), day(day), time(time) {}
        // Get Class Day
        std::string getDay() const {
            return this -> day;
        }
        // Get Time of Class
        std::string getTime() const {
            return this -> time;
        }
};

#endif
