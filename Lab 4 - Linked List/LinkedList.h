#ifndef LinkedList_h
#define LinkedList_h
#include <stdio.h>
#include <sstream>
#include <iostream>
#include "LinkedListInterface.h"

template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    size_t listSize;
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(NULL) {}
        Node(const T& d, Node* n) : data(d), next(n) {}
        ~Node() {
            delete next;
        }
    };
    Node* head = nullptr;
    
    size_t findNode(T value) const {
        if (listSize > 0 && head -> data == value) return 0;
        if (listSize > 1) {
            Node* currentNode = head;
            for (size_t i = 0; currentNode; ++i, currentNode = currentNode -> next) {
                if (currentNode -> data == value) return i;
            }
        }
        return -1;
    }
    Node* getNode(size_t index) const {
        if (index == 0) return head;
        else {
            Node* currentNode = head;
            for (size_t i = 0; currentNode; ++i, currentNode = currentNode -> next) {
                if (i == index) return currentNode;
            }
            return NULL;
        }
    }
public:
    LinkedList(void) : listSize(0) {}
    virtual ~LinkedList(void) {
        delete head;
    }
    class Iterator {
    private:
        size_t index_;
        LinkedList<T>* array_ptr_;
    public:
        // Initilize iterator for MyArray
        Iterator(LinkedList<T>* a, size_t s) : array_ptr_(a), index_(s) {}
        // Print string with iterator info
        std::string toString() const {
            std::ostringstream out;
            out << "size=" << array_ptr_ -> listSize << " index=" << index_;
            return out.str();
        }
        // Overload << operator to print Iterator info
        friend std::ostream& operator<<(std::ostream& os, Iterator it) {
            os << it.toString();
            return os;
        }
        // Overload [] operator for iterator
        T operator[](size_t i) const {
            array_ptr_ -> array_ -> at(i);
        }
        // Overload * dereference operator for iterator
        T& operator*() {
            return array_ptr_ -> at(index_);
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
        return LinkedList<T>::Iterator(this, 0);
    }
    // Get iterator for element past last element in array
    Iterator end() {
        return LinkedList<T>::Iterator(this, listSize);
    }
    /** Insert Node at beginning of linked list (no duplicates) */
    virtual bool insertHead(T value) {
        size_t loc = findNode(value);
        
        if (loc != -1) return false;
        else if (head == nullptr) head = new Node(value);
        else if (head -> data != value) head = new Node(value, head);
        
        ++listSize;
        return true;
    }
    /** Insert Node at end of linked list (no duplicates) */
    virtual bool insertTail(T value) {
        if (head == nullptr) {
            head = new Node(value);
            listSize++;
        }
        else {
            Node* tail = head;
            while (tail -> next) {
                tail = tail -> next;
                if (tail -> data == value) return false;
            }
            
            Node* insert = new Node(value);
            tail -> next = insert;
            listSize++;
        }
        return true;
    }
    /** Print the nodes in the linked list */
    std::string printList() const {
        std::ostringstream out;
        if (listSize > 0) {
            Node* currentNode = head;
            out << currentNode -> data << " ";
            while ((currentNode = currentNode -> next)) {
                out << currentNode -> data << " ";
            }
        } else out << "Empty";
        return out.str();
    }
    /** Insert Node after matching Node (no duplicates) */
    virtual bool insertAfter(T matchValue, T value) {
        size_t loc = findNode(value), locMatch = findNode(matchValue);
        if (loc != -1 || locMatch == -1) return false;
        else {
            Node* match = getNode(locMatch);
            Node* afterMatch = getNode(locMatch + 1);
            Node* insert = new Node(value);
            match -> next = insert;
            insert -> next = afterMatch;
            listSize++;
            return true;
        }
    }
    /** Remove Node from linked list */
    virtual bool remove(T value) {
        Node* ptr = head;
        if (this -> findNode(value)) {
            while (ptr != NULL) {
                if (value == head -> data) {
                    Node* newptr = ptr;
                    head = newptr -> next;
                    delete newptr;
                    return true;
                }
                if (ptr -> next -> data == value) {
                    Node* newptr = ptr -> next;
                    ptr -> next = ptr -> next -> next;
                    delete newptr;
                    return true;
                }
                ptr = ptr -> next;
            }
        }
        return false;
    }
    /** Remove all Nodes from linked list */
    virtual bool clear() {
        while (listSize > 0) remove(at(0));
        listSize = 0;
        return true;
    }
    /** Return a reference to the value at Node(index)
     Throw an error if out of range.
     NOTE: STL list does NOT support the at accessor. */
    virtual T& at(size_t index) {
        if (index >= listSize || index < 0) throw "Invalid Index";
        Node* out = head;
        for (size_t i = 0; i < index; ++i) {
            out = out -> next;
        }
        return out -> data;
    }
    /** Return the number of nodes in the linked list */
    virtual size_t size() const {
        return listSize;
    }
    /** Return a level order traversal of a Linked List as a string */
    virtual std::string toString() const {
        std::ostringstream out;
        Node* current = head;
        while (current -> next) {
            out << current -> data << " ";
            current = current -> next;
        }
        return out.str();
    }
    /** Iterate list using iterator */
    std::string iterateList() {
        std::ostringstream out;
        LinkedList<T>::Iterator iter = begin();
        std::cout << "[-] Start" << std::endl;
        for (int i = 0; iter != end(); ++iter, ++i) {
            out << *iter << " ";
            std::cout << out.str() << std::endl;
        }
        return out.str();
    }
};

#endif
