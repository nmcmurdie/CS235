#ifndef Deque_h
#define Deque_h
#include <sstream>
#include "DequeInterface.h"

template<typename T>
class Deque : public DequeInterface<T> {
private:
    size_t capacity, numItems, frontIndex, rearIndex;
    T* data;

    /** Expand data size */
    void reallocate() {
        size_t newCapacity = 2 * capacity, endSize = .5 * capacity;
        T* newData = new T[newCapacity];
        for (size_t i = endSize, j = frontIndex; i < endSize + numItems; ++i, ++j) {
            newData[i] = data[j];
        }
        frontIndex = endSize;
        rearIndex = endSize + numItems - 1;
        capacity = newCapacity;
        std::swap(data, newData);
        delete[] newData;
    }

    /** Overload extraction operator */
    friend std::ostream& operator<<(std::ostream& out, Deque d) {
        out << d.toString();
        return out;
    }

public:
    /** Initialize deque with default capacity */
    Deque(void) : capacity(DEFAULT_CAPACITY), numItems(0), frontIndex(1), rearIndex(1),
        data(new T[DEFAULT_CAPACITY]) {}

    /** Free data allocated by deque */
    ~Deque(void) {
        delete[] data;
    }

    /** Return the deque items */
    virtual std::string toString(void) const {
        std::ostringstream out;
        for (size_t i = frontIndex; i <= rearIndex; ++i) {
            if (i > frontIndex) out << " ";
            out << data[i];
        }
        return out.str();
    }

    /** Return the number of items in the deque */
    virtual size_t size(void) const {
        return this -> numItems;
    }

    /** Return true if deque is empty */
    virtual bool empty(void) const {
        return this -> numItems == 0;
    }

    /** Insert item at rear of deque */
    virtual void push_back(const T& value) {
        if (rearIndex + 1 == capacity) reallocate();
        if (!empty()) data[++rearIndex] = value;
        else data[rearIndex] = value;
        ++numItems;
    }

    /** Insert item at front of deque */
    virtual void push_front(const T& value) {
        if (frontIndex == 0) reallocate();
        if (!empty()) data[--frontIndex] = value;
        else data[frontIndex] = value;
        ++numItems;
    }

    /** Remove the front item of the deque */
    virtual void pop_front(void) {
        if (numItems > 1) ++frontIndex;
        --numItems;
    }

    /** Remove the rear item of the deque */
    virtual void pop_back(void) {
        if (numItems > 1) --rearIndex;
        --numItems;
    }

    /** Return the front item of the deque (Do not remove) */
    virtual T& front(void) {
        return data[frontIndex];
    }

    /** Return the rear item of the deque (Do not remove) */
    virtual T& back(void) {
        return data[rearIndex];
    }

    /** Return item in deque at index (0 based) */
    virtual T& at(size_t index) {
        if (frontIndex + index < capacity) return data[frontIndex + index];
        else return data[frontIndex + index];
    }

    /** Find item in deque */
    size_t find(const T& item) {
        for (size_t i = frontIndex; i <= rearIndex; ++i) {
            if (data[i] == item) return i;
        }
        return -1;
    }
};

#endif
