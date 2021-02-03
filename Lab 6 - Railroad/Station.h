#ifndef Station_h
#define Station_h
#include <sstream>
#include "Queue.h"
#include "Stack.h"
#include "Vector.h"

template<typename T>
class Station {
private:
    Stack<T> stack;
    Queue<T> queue;
    Vector<T> train;
    T turnTable = -1;
    
public:
    /** Initialize station data */
    Station(void) {}
    
    /** Add car to turntable */
    std::string addCar(T& car) {
        if (turnTable != -1) return "Turntable occupied!";
        else turnTable = car;
        return "OK";
    }
    
    /** Add car to stack */
    std::string addStack() {
        if (turnTable == -1) return "Turntable empty!";
        else {
            stack.push(turnTable);
            turnTable = -1;
            return "OK";
        }
    }
    
    /** Add car to queue */
    std::string addQueue() {
        if (turnTable == -1) return "Turntable empty!";
        else {
            queue.push(turnTable);
            turnTable = -1;
            return "OK";
        }
    }
    
    /** Remove car from turntable */
    std::string removeCar() {
        if (turnTable == -1) return "Turntable empty!";
        else {
            train.push_back(turnTable);
            turnTable = -1;
            return "OK";
        }
    }
    
    /** Remove car from stack */
    std::string removeStack() {
        if (turnTable != -1) return "Turntable Occupied!";
        else if (stack.size() == 0) return "Stack empty!";
        else {
            turnTable = stack.top();
            stack.pop();
            return "OK";
        }
    }
    
    /** Remove car from queue */
    std::string removeQueue() {
        if (turnTable != -1) return "Turntable Occupied!";
        else if (queue.size() == 0) return "Queue empty!";
        else {
            turnTable = queue.top();
            queue.pop();
            return "OK";
        }
    }
    
    /** Get top car of turntable */
    std::string topCar() {
        if (turnTable == -1) return "Turntable empty!";
        else return std::to_string(turnTable);
    }
    
    /** Remove car from stack */
    std::string topStack() {
        if (stack.size() == 0) return "Stack empty!";
        else return std::to_string(stack.top());
    }
    
    /** Remove car from queue */
    std::string topQueue() {
        if (queue.size() == 0) return "Queue empty!";
        else return std::to_string(queue.top());
    }
    
    /** Return size of stack */
    std::string sizeStack() {
        return std::to_string(stack.size());
    }
    
    /** Return size of queue */
    std::string sizeQueue() {
        return std::to_string(queue.size());
    }
    
    /** Print train */
    std::string toString() {
        std::ostringstream out;
        for (size_t i = 0; i < train.size(); ++i) {
            out << " " << train.at(i);
        }
        return out.str();
    }
    
    /** Find item in data structures */
    std::string find(const T& car) {
        std::ostringstream out;
        if (turnTable == car) return "Turntable";
        else if ((int) queue.find(car) != -1) {
            out << "Queue[" << (queue.find(car) - 1) << "]";
            return out.str();
        }
        else if ((int) stack.find(car) != -1) {
            out << "Stack[" << (stack.find(car) - 1) << "]";
            return out.str();
        }
        else if ((int) train.find(car) != -1) {
            out << "Train[" << (train.find(car) - 1) << "]";
            return out.str();
        }
        else return "Not Found!";
    }
};

#endif
