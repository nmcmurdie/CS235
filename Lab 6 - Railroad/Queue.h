#ifndef Queue_h
#define Queue_h
#include "Deque.h"

template<typename T>

class Queue {
private:
    Deque<T> data;

public:
    /** Initialize Queue data */
    Queue(void) {}

    /** Push element to end of deque */
    void push(const T& value) {
        data.push_back(value);
    }

    /** Pop element from front of deque */
    void pop() {
        data.pop_front();
    }

    /** Get element on top of queue */
    T& top() {
        return data.front();
    }

    /** Return queue as string */
    std::string toString() const {
        return data.toString();
    }

    /** Get size of queue */
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
