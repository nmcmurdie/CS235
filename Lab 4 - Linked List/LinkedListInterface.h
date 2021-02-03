//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef LINKED_LIST_INTERFACE_H
#define LINKED_LIST_INTERFACE_H
#include <string>

template<typename T>
class LinkedListInterface {
public:
    LinkedListInterface(void) {};
    virtual ~LinkedListInterface(void) {};
    
    /** Insert Node at beginning of linked list (no duplicates) */
    virtual bool insertHead(T value) = 0;
    
    /** Insert Node at end of linked list (no duplicates) */
    virtual bool insertTail(T value) = 0;
    
    /** Insert Node after matching Node (no duplicates) */
    virtual bool insertAfter(T matchValue, T value) = 0;
    
    /** Remove Node from linked list */
    virtual bool remove(T value) = 0;
    
    /** Remove all Nodes from linked list */
    virtual bool clear() = 0;
    
    /** Return a reference to the value at Node(index)
     Throw an error if out of range.
     NOTE: STL list does NOT support the at accessor. */
    virtual T& at(size_t index) = 0;
    
    /** Return the number of nodes in the linked list */
    virtual size_t size() const = 0;
    
    /** Return a level order traversal of a Linked List as a string */
    virtual std::string toString() const = 0;
};
#endif    // LINKED_LIST_INTERFACE_H
