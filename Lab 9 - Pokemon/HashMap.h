#ifndef HASHMAP_H
#define HASHMAP_H
#include <utility>
#include <sstream>
#include "HashMapInterface.h"

template <typename KEY, typename VALUE>
class HashMap : public HashMapInterface<KEY, VALUE> {
private:
    size_t capacity, numItems;
    std::pair<KEY, VALUE>* myPairs;
    
    /** Double array size and rehash when 75% full */
    void reallocate();
    
    /** Perform insert function for reallocate and indexing operator */
    VALUE& insert(std::pair<KEY, VALUE>* data, size_t cap, const KEY& key);
    
    /** Overload << operator so Set can be printed with HashMap */
    friend std::ostream& operator<<(std::ostream& out, HashMap& data) {
        out << data.toString();
        return out;
    }
    
public:
    /** Initialize HashMap with default capacity */
    HashMap<KEY, VALUE>() : myPairs(new std::pair<KEY, VALUE>[DEFAULT_MAP_HASH_TABLE_SIZE]), capacity(DEFAULT_MAP_HASH_TABLE_SIZE), numItems(0) {}
    
    /** Free memory allocated by HashMap */
    ~HashMap() {
        delete[] myPairs;
    }
    
    /** Read/write index access operator.
     If the key is not found, an entry is made for it.
     @return: Read and write access to the value mapped to the provided key. */
    VALUE& operator[](const KEY& key) {
        if (static_cast<double>(numItems) / capacity * 100 > LOAD_THRESHOLD) reallocate();
        return insert(myPairs, capacity, key);
    }
    
    /** @return: the number of elements that match the key in the Map. */
    virtual size_t count(const KEY& key) {
        size_t numMatches = 0;
        for (size_t i = 0; i < capacity; ++i) {
            if (myPairs[i].first == key) ++numMatches;
        }
        return numMatches;
    }
    
    /** Removes all items from the Map. */
    virtual void clear(void);
    
    /** @return: number of Key-Value pairs stored in the Map. */
    virtual size_t size(void) const {
        return numItems;
    }
    
    /** @return: maximum number of Key-Value pairs that the Map can hold. (Can't be upper camelCase because of HashMapInterface) */
    virtual size_t max_size(void) const {
        return capacity;
    }
    
    /** @return: string representation of Key-Value pairs in Map (<10 lines so can be in class) */
    std::string toString() const {
        std::ostringstream os;
        os << numItems << "/" << capacity << std::endl;
        for (size_t i = 0; i < capacity; ++i) {
            if (myPairs[i].first.length()) {
                os << "[" << i << ":" << myPairs[i].first << "->" << myPairs[i].second << "]" << std::endl;
            }
        }
        return os.str();
    }
};

/** Perform insert function for reallocate and indexing operator (Outside of class since >10 lines) */
template<typename KEY, typename VALUE>
VALUE& HashMap<KEY, VALUE>::insert(std::pair<KEY, VALUE>* data, size_t cap, const KEY& key) {
    long long hash = key[0];
    for (size_t i = 1; i < key.length(); ++i) {
        hash = hash * HASH_CONSTANT + key[i];
    }
    hash %= cap;
    for (int k = 1; 1;) {
        if (data[hash].first.length()) {
            if (data[hash].first == key) break;
            hash = (hash + k) % cap;
            k += 2;
            continue;
        }
        data[hash].first = key;
        ++numItems;
        break;
    }
    return data[hash].second;
}

/** Removes all items from the Map
    (Outside of class since data is instantiated, can't be in .cpp since class is templated) */
template<typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::clear(void) {
    delete[] myPairs;
    myPairs = new std::pair<KEY, VALUE>[DEFAULT_MAP_HASH_TABLE_SIZE];
    numItems = 0;
}

/** Double array size and rehash using insert() when 75% full
    (Outside of class since data is instantiated, can't be in .cpp since class is templated) */
template<typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::reallocate() {
    size_t newCapacity = 2 * capacity;
    std::pair<KEY, VALUE>* newData = new std::pair<KEY, VALUE>[newCapacity];
    numItems = 0;
    
    for (int i = 0; i < capacity; ++i) {
        if (myPairs[i].first.length()) insert(newData, newCapacity, myPairs[i].first) = myPairs[i].second;
    }
    
    capacity = newCapacity;
    std::swap(myPairs, newData);
    delete[] newData;
}

#endif
