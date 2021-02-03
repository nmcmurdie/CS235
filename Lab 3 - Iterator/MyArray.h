#ifndef MyArray_h
#define MyArray_h

#include <stdio.h>
#include <iostream>
#include <sstream>
#define MAX_ARRAY_SIZE   1000
using namespace std;

template<typename T>
class MyArray {
    private:
        size_t size_;
        T* array_;
    
        // Print array as string with 10 numbers / line
        std::string toString() const {
            ostringstream out;
            for (unsigned int i = 0; i < size_; ++i) {
                out << array_[i] << " ";
                if ((i + 1) % 10 == 0) out << endl;
            }
            return out.str();
        }
    public:
        // Initilize MyArray and allocate memory for 1000 elements
        MyArray(size_t maxSize = MAX_ARRAY_SIZE) : size_(0) {
            array_ = (T*)malloc(maxSize * sizeof(T));
        }
        // Copy data to a new MyArray that gets created by toString
        MyArray(const MyArray& obj) : MyArray(obj.size_) {
            size_ = obj.size_;
            for (unsigned int i = 0; i < size_; ++i) array_[i] = obj.array_[i];
        }
        // Free memory allocated by array
        ~MyArray() {
            free(array_);
        }
        // Push element to end of MyArray
        void push_back(T item) {
            array_[size_++] = item;
        }
        // Overload << operator to print array info
        friend ostream& operator<<(ostream& os, MyArray arr) {
            os << arr.toString();
            return os;
        }
    
        class Iterator {
            private:
                size_t index_;
                MyArray<T>* array_ptr_;
            public:
                // Initilize iterator for MyArray
                Iterator(MyArray<T>* a, size_t s) : array_ptr_(a), index_(s) {}
                // Print string with iterator info
                string toString() const {
                    ostringstream out;
                    out << "size=" << array_ptr_ -> size_ << " index=" << index_;
                    return out.str();
                }
                // Overload << operator to print Iterator info
                friend ostream& operator<<(ostream& os, Iterator it) {
                    os << it.toString();
                    return os;
                }
                // Overload [] operator for iterator
                T operator[](size_t i) const {
                    array_ptr_ -> array_[i];
                }
                // Overload * dereference operator for iterator
                T& operator*() {
                    return array_ptr_ -> array_[index_];
                }
                // Overload ++ pre increment operator for iterator
                Iterator& operator++() {
                    index_++;
                    return *this;
                }
                // Overload != so iterator can be compared to another iterator
                bool operator!=(Iterator it) {
                    return (it.toString() != this -> toString());
                }
        };
        // Get iterator for first element in array
        Iterator begin() {
            return MyArray<T>::Iterator(this, 0);
        }
        // Get iterator for element past last element in array
        Iterator end() {
            return MyArray<T>::Iterator(this, size_);
        }
};


#endif
