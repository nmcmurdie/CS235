#ifndef CR_h
#define CR_h

#include <stdio.h>
#include "CourseInfo.h"

class CR : public CourseInfo {
    private:
        std::string room = "";
        // Print class, called by << operator
        virtual std::string toString() const {
            std::ostringstream out;
            out << "cr" << CourseInfo::toString() << room << ")";
            return out.str();
        }
    public:
        CR(std::string className = "", std::string room = "") : CourseInfo(className), room(room) {}
        // Get Class Room
        std::string getRoom() const {
            return this -> room;
        }
};

#endif
