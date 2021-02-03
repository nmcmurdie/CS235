#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <list>
#include <sstream>
#include "SetInterface.h"

template<typename T>
class Set : public SetInterface<T> {
private:
    std::list<T> data;
    
    /** Overload << operator so Set can be printed with HashMap */
    friend std::ostream& operator<<(std::ostream& out, Set& data) {
        out << data.toString();
        return out;
    }
    
public:
    /** Inserts item into the set, if the container doesn't
     already contain an element with an equivalent value.
     @return: pair.first = pointer to item
     pair.second = true if successfully inserted, else false. */
    virtual bool insert(const T& item) {
        if (count(item)) return false;
        data.push_back(item);
        data.sort(std::less<T>());
        return true;
    }
    
    /** Removes all items from the set. */
    virtual void clear() {
        data.clear();
    }
    
    /** @return: the number of elements contained by the Set. */
    virtual size_t size() const {
        return data.size();
    }
    
    /** @return: return 1 if contains element equivalent to item, else 0. (Can't be const because of SetInterface)  */
    virtual size_t count(const T& item) {
        for (T const& i : data) {
            if (item == i) return 1;
        }
        return 0;
    }
    
    /** @return: string representation of items in Set (<10 lines so can be in class) */
    virtual std::string toString() const {
        std::ostringstream out;
        bool firstElem = true;
        for (T const& item : data) {
            if (firstElem) firstElem = false;
            else out << ",";
            out << item;
        }
        return out.str();
    }
};

#endif
