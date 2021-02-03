#ifndef SNAP_h
#define SNAP_h

#include <stdio.h>
#include <sstream>

class SNAP {
    private:
        std::string studentID = "";
        std::string studentName = "";
        std::string studentTitle = "";
        std::string phoneNumber = "";
        // Print class, called by << operator
        std::string toString() const {
            std::ostringstream out;
            out << "snap(" << studentID << "," << studentName << ","
                << studentTitle << "," << phoneNumber << ")" << std::endl;
            return out.str();
        }
    public:
        SNAP(std::string studentID = "", std::string studentName = "", std::string studentTitle = "", std::string phoneNumber = "") :
            studentID(studentID), studentName(studentName), studentTitle(studentTitle),
            phoneNumber(phoneNumber) {}
        // Overload << operator so classes can be printed using ostream
        friend std::ostream& operator<<(std::ostream& os, SNAP& myClass) {
            os << myClass.toString();
            return os;
        }
        // Get Student ID
        std::string getID() const {
            return this -> studentID;
        }
        // Get Student Name
        std::string getName() const {
            return this -> studentName;
        }
        // Get Student Title
        std::string getTitle() const {
            return this -> studentTitle;
        }
        // Get Student Phone Number
        std::string getPhoneNumber() const {
            return this -> phoneNumber;
        }
};

#endif
