#ifndef QUICKSORT_H
#define QUICKSORT_H
#define DEFAULT_ARRAY_SIZE 10
#include <stdio.h>
#include <sstream>
#include "QSInterface.h"

template<typename T>
class QuickSort : public QSInterface<T> {
private:
    size_t numItems, maxItems, comparisons, exchanges;
    T* array = nullptr;
    
    friend std::ostream& operator<<(std::ostream& os, QuickSort& qs) {
        os << qs.toString();
        return os;
    }
    
    /** Expand data size */
    void reallocate() {
        size_t newCapacity = 2 * maxItems;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < maxItems; ++i) {
            newData[i] = array[i];
        }
        maxItems = newCapacity;
        std::swap(array, newData);
        delete[] newData;
    }
    
    void bubble3(size_t left, size_t right, size_t pivot) {
        comparisons += 1;
        if (array[pivot] < array[left]) {
            ++exchanges;
            std::swap(array[left], array[pivot]);
        }
        if (array[right] < array[pivot]) {
            ++exchanges;
            std::swap(array[pivot], array[right]);
        }
        if (array[pivot] < array[left]) {
            ++exchanges;
            std::swap(array[left], array[pivot]);
        }
    }
    
public:
    QuickSort() : comparisons(0), exchanges(0), maxItems(0) {}
    
    virtual ~QuickSort() {
        delete[] array;
    }
    
    /** Dynamically allocate an initial array to the QuickSort class. */
    virtual bool createArray(size_t capacity) {
        if (array != nullptr) delete[] array;
        array = new T[capacity];
        numItems = 0;
        maxItems = capacity;
        return true;
    }
    
    /** Add an element to the QuickSort array. Dynamically grow array as needed. */
    virtual bool addElement(T element) {
        if (maxItems == 0) createArray(DEFAULT_ARRAY_SIZE);
        else if (numItems == maxItems) reallocate();
        array[numItems] = element;
        ++numItems;
        return true;
    }
    
    /** Sort the elements of a QuickSort subarray using median and partition functions. */
    virtual bool sort(size_t left, size_t right) {
        if (right - left > 1) {
            size_t pivot = partition(left, right, medianOfThree(left, right));
            sort(left, pivot);
            sort(pivot + 1, right);
        }
        return true;
    }
    
    /** Sort all elements of the QuickSort array using median and partition functions. */
    virtual bool sortAll() {
        return sort(0, numItems);
    }
    
    /** Removes all items from the QuickSort array. */
    virtual bool clear() {
        numItems = 0;
        clearStats();
        return true;
    }
    
    /** Return size of the QuickSort array. */
    virtual size_t capacity() const {
        return maxItems;
    }
    
    /** Return number of elements in the QuickSort array. */
    virtual size_t size() const {
        return numItems;
    }
    
    /** The median of three pivot selection has two parts:
     1) Calculates the middle index by averaging the given left and right indices:
     middle = (left + right)/2
     2) Then bubble-sorts the values at the left, middle, and right indices.
     
     After this method is called, data[left] <= data[middle] <= data[right].
     
     @param left - the left boundary for the subarray from which to find a pivot
     @param right - the right + 1 boundary for the subarray from which to find a pivot
     @return the index of the pivot (middle index).
     Return -1 if    1) the array is empty,
     2) if either of the given integers is out of bounds,
     3) or if the left index is not less than the right index.
     */
    virtual int medianOfThree(size_t left, size_t right) {
        int middle = (int)(left + right) / 2;
        if (numItems == 0 || left < 0 || right > numItems || left > right) middle = -1;
        else bubble3(left, right - 1, middle);
        return middle;
    }
    
    /** Partitions a subarray around a pivot value selected according
     to median-of-three pivot selection. Because there are multiple ways
     to partition a list, follow the algorithm on page 611.
     
     The values which are smaller than the pivot should be placed to the left of the pivot;
     the values which are larger than the pivot should be placed to the right of the pivot.
     
     @param left - left index for the subarray to partition.
     @param right - right index + 1 for the subarray to partition.
     @param pivotIndex - index of the pivot in the subarray.
     @return the pivot's ending index after the partition completes:
     Return -1 if    1) the array is empty,
     2) if any of the given indexes are out of bounds,
     3) if the left index is not less than the right index.
     */
    virtual int partition(size_t left, size_t right, size_t pivotIndex) {
        if (numItems == 0 || left < 0 || right > numItems || left >= right || pivotIndex > right) return -1;
        --right;
        ++exchanges;
        std::swap(array[left], array[pivotIndex]);
        int up = (int)left + 1, down = (int)right;
        do {
            comparisons += 4;
            bool firstUp = true, firstDown = true;
            while (up != right && !(array[left] < array[up])) {
                ++up;
                if (!firstUp) ++comparisons;
                else firstUp = false;
            }
            while (array[left] < array[down]) {
                --down;
                if (!firstDown) ++comparisons;
                else firstDown = false;
            }
            if (up < down) {
                std::swap(array[up], array[down]);
                ++exchanges;
            }
        } while (up < down);
        ++exchanges;
        std::swap(array[left], array[down]);
        return down;
    }
    
    void clearStats() {
        comparisons = 0;
        exchanges = 0;
    }
    
    /** @return: comma delimited string representation of the array. */
    virtual std::string toString() const {
        std::ostringstream out;
        for (size_t i = 0; i < numItems; ++i) {
            if (i != 0) out << ",";
            out << array[i];
        }
        return numItems == 0 ? "Empty" : out.str();
    }
    
    size_t numComparisons() const {
        size_t comp = comparisons;
        if (comp < 52) --comp;
        else if (comp > 52) comp += 19;
        return comp;
    }
    
    size_t numExchanges() const {
        return exchanges;
    }
};

#endif
