#ifndef COURSEINFO_h
#define COURSEINFO_h

#include <stdio.h>
#include <sstream>

class CourseInfo {
    private:
        std::string className = "";
    public:
        CourseInfo(std::string className = "") : className(className) {}
        // Overload << operator so classes can be printed using ostream
        friend std::ostream& operator<< (std::ostream& os, const CourseInfo& myClass) {
            os << myClass.toString() << std::endl;
            return os;
        }
        // Get Name of Class
        std::string getClassName() const {
            return this -> className;
        }
    protected:
        // Print class, called by << operator
        virtual std::string toString() const {
            std::ostringstream out;
            out << "(" << this -> className << ",";
            return out.str();
        }
};

#endif
