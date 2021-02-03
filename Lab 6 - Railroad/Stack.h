#ifndef Stack_h
#define Stack_h
#include "Deque.h"

template<typename T>

class Stack {
private:
    Deque<T> data;
    
public:
    /** Initialize Stack data */
    Stack(void) {}
    
    /** Push element to end of deque */
    void push(const T& value) {
        data.push_back(value);
    }
    
    /** Pop element from back of deque */
    void pop() {
        data.pop_back();
    }
    
    /** Get element on top of stack */
    T& top() {
        return data.back();
    }
    
    /** Return stack as string */
    std::string toString() const {
        return data.toString();
    }
    
    /** Get size of stack */
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

