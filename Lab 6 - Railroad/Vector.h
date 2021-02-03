#ifndef Vector_h
#define Vector_h
#include "Deque.h"

template<typename T>

class Vector {
private:
    Deque<T> data;
    
public:
    /** Initialize Vector data */
    Vector(void) {}
    
    /** Push element to end of deque */
    void push_back(const T& value) {
        data.push_back(value);
    }
    
    /** Pop element from back of deque */
    void pop_back() {
        data.pop_back();
    }
    
    /** Get element on back of vector */
    T& back() {
        return data.back();
    }
    
    /** Return vector as string */
    std::string toString() const {
        return data.toString();
    }
    
    /** Get size of vector */
    size_t size() const {
        return data.size();
    }
    
    /** Get element at index */
    T& at(size_t index) {
        return data.at(index);
    }
    
    /** Find item in data */
    size_t find(const T& item) {
        return data.find(item);
    }
};

#endif


