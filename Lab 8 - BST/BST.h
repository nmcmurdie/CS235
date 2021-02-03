#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <sstream>
#include "BSTInterface.h"

template<typename T>
class BST : public BSTInterface<T> {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        /** Initialize node with data and NULL links */
        Node(const T& d) : data(d), left(NULL), right(NULL) {}
        
        /** Delete links when destroyed (Allows recursive tree memory reallocation) */
        ~Node() {
            delete left;
            delete right;
        }
    };
    
    Node* root;
    size_t size;
    
    /** Recursive function to find a node called by findNode() */
    bool find(const T& data, Node* node) const {
        if (node == NULL) return false;
        else if (data < node -> data) return find(data, node -> left);
        else if (data > node -> data) return find(data, node -> right);
        return true;
    }
    
    /** Find in-order predecessor to a node, used by remove() */
    Node* inPredecessor(Node* node) const {
        if (node != NULL && node -> right) return inPredecessor(node -> right);
        return node;
    }
    
    /** Recursive function to remove called by removeNode() */
    bool remove(const T& data, Node*& node);
    
    /** Output nodes at a given level */
    bool outLevel(Node* node, int level, std::ostream& out) const;
    
    /** Add node to BST (Implemented outside of class) */
    bool add(const T& data, Node*& node);
    
public:
    /** Initialize BST */
    BST(void) : root(NULL), size(0) {}
    
    /** Free memory allocated by BST */
    ~BST(void) {
        clearTree();
    }
    
    /** Return true if node added to BST, else false */
    virtual bool addNode(const T& data) {
        return add(data, root);
    }
    
    /** Return true if node removed from BST, else false */
    virtual bool removeNode(const T& data) {
        return remove(data, root);
    }
    
    /** Return true if BST cleared of all nodes, else false */
    virtual bool clearTree() {
        delete root;
        root = NULL;
        size = 0;
        return true;
    }
    
    /** Find node in tree recursively */
    bool findNode(const T& data) const {
        return find(data, root);
    }
    
    /** Get size of BST */
    size_t getSize() const {
        return size;
    }
    
    /** Return a level order traversal of a BST as a string */
    virtual std::string toString() const {
        std::ostringstream out;
        if (root == NULL) return " empty";
        int level = -1;
        do {
            out << std::endl << ++level + 1 << ":";
        } while (outLevel(root, level, out));
        return out.str();
    }
    
    /** Call toString when class is used with output stream */
    friend std::ostream& operator<<(std::ostream& out, BST &obj) {
        out << obj.toString();
        return out;
    }
};

/** Recursive function to remove called by removeNode() (Outside class since >10 lines) */
template<typename T>
bool BST<T>::remove(const T& data, Node*& node) {
    // Find node, then determine which of the 3 cases applies: 0 children, 1 children, or 2 children
    if (node == NULL) return false;
    else if (data < node -> data) return remove(data, node -> left);
    else if (data > node -> data) return remove(data, node -> right);
    else if (!node -> left && !node -> right) {
        // If no children, just delete the node
        delete node;
        node = NULL;
        --size;
        return true;
    }
    else if (node -> left && !node -> right) {
        // If one child (left), swap data between parent and child
        node -> data = node -> left -> data;
        delete node -> left;
        node -> left = NULL;
        --size;
        return true;
    }
    else if (node -> right && !node -> left) {
        // If one child (right), swap data between parent and child
        node -> data = node -> right -> data;
        delete node -> right;
        node -> right = NULL;
        --size;
        return true;
    }
    // If 2 children, replace parent with in-order predecessor then remove on parent's left child
    Node* pre = inPredecessor(node -> left);
    std::swap(node -> data, pre -> data);
    return remove(data, node -> left);
}

/** Output nodes at a given level (Outside class since >10 lines) */
template<typename T>
bool BST<T>::outLevel(Node* node, int level, std::ostream& out) const {
    if (node == NULL) return false;
    else if (level == 0) {
        out << " " << node -> data;
        if (node -> left != NULL || node -> right != NULL) return true;
        return false;
    }
    else if (level == 1 && !node -> left && node -> right) out << " _";
    bool left = outLevel(node -> left, level - 1, out);
    bool right = outLevel(node -> right, level - 1, out);
    if (level == 1 && node -> left && !node -> right) out << " _";
    return left || right;
}

/** Recursive function to add called by addNode (Outside class since it instantiates data, cannot be in .cpp since class is templated) */
template<typename T>
bool BST<T>::add(const T& data, Node*& node) {
    if (node == NULL) {
        node = new Node(data);
        ++size;
        return true;
    }
    else if (data < node -> data) return add(data, node -> left);
    else if (data > node -> data) return add(data, node -> right);
    else return false;
}

#endif
