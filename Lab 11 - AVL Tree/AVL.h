#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "AVLInterface.h"

template<typename T>
class AVL : public AVLInterface<T> {
private:
    struct Node {
        enum balanceType {LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1};
        balanceType balance;
        T data;
        Node* left;
        Node* right;
        
        /** Initialize node with data and NULL links */
        Node(const T& d) : data(d), left(NULL), right(NULL), balance(BALANCED) {}
    };
    
    Node* root;
    size_t size;
    bool increase = false, decrease = false;
    
    bool resetTree(Node*& node) {
        deleteTree(node);
        size--;
        root = NULL;
        return true;
    }
    
    bool deleteTree(Node*& node) {
        if (node == NULL) return true;
        if (node -> left) deleteTree(node -> left);
        if (node -> right) deleteTree(node -> right);
        
        delete node;
        return true;
    }
    
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
    
    void rotateLeft(Node*& root) {
        Node* temp = root -> right;
        if (!temp) return;
        
        root -> right = temp -> left;
        temp -> left = root;
        root = temp;
    }
    
    void rotateRight(Node*& root) {
        Node* temp = root -> left;
        if (!temp) return;
        
        root -> left = temp -> right;
        temp -> right = root;
        root = temp;
    }
    
    bool insert(Node*& root, const T& data) {
        if (root == NULL) {
            root = new Node(data);
            increase = true;
            return true;
        }
        if (data < root -> data) {
            bool returnValue = insert(root -> left, data);
            
            if (increase) {
                switch (root -> balance) {
                    case Node::BALANCED:
                        root -> balance = Node::LEFT_HEAVY;
                        break;
                    case Node::RIGHT_HEAVY:
                        root -> balance = Node::BALANCED;
                        increase = false;
                        break;
                    case Node::LEFT_HEAVY:
                        rebalanceLeft(root);
                        increase = false;
                        break;
                }
            }
            return returnValue;
        } else if (data > root -> data) {
            bool returnValue = insert(root -> right, data);
            
            if (increase) {
                switch (root -> balance) {
                    case Node::BALANCED:
                        root -> balance = Node::RIGHT_HEAVY;
                        break;
                    case Node::RIGHT_HEAVY:
                        rebalanceRight(root);
                        increase = false;
                        break;
                    case Node::LEFT_HEAVY:
                        root -> balance = Node::BALANCED;
                        increase = false;
                        break;
                }
            }
            return returnValue;
        } else {
            increase = false;
            return false;
        }
    }
    
    size_t height(Node* root, const T& data) const {
        if (root == NULL) return 0;
        else if (data < root -> data) return 1 + height(root -> left, data);
        else if (data > root -> data) return 1 + height(root -> right, data);
        
        return 0;
    }
    
public:
    /** Initialize BST */
    AVL(void) : root(NULL), size(0) {}
    
    /** Free memory allocated by BST */
    ~AVL(void) {
        clearTree();
    }
    
    /** Return true if node added to BST, else false */
    virtual bool addNode(const T& data) {
        return add(data, root);
    }
    
    bool insertNode(const T& data) {
        return insert(this -> root, data);
    }
    
    void rebalanceLeft(Node*& root) {
        Node* leftChild = root -> left ? root -> left : NULL;
        
        if (leftChild && leftChild -> balance == Node::RIGHT_HEAVY) {
            Node* leftRightChild = leftChild -> right ? leftChild -> right : NULL;
            
            if (leftRightChild && leftRightChild -> balance == Node::LEFT_HEAVY) {
                leftChild -> balance = Node::BALANCED;
                leftRightChild -> balance = Node::BALANCED;
                root -> balance = Node::RIGHT_HEAVY;
            }
            else if (leftRightChild && leftRightChild -> balance == Node::BALANCED) {
                leftChild -> balance = Node::BALANCED;
                leftRightChild -> balance = Node::BALANCED;
                root -> balance = Node::BALANCED;
            }
            else if (leftRightChild){
                leftChild -> balance = Node::LEFT_HEAVY;
                leftRightChild -> balance = Node::BALANCED;
                root -> balance = Node::BALANCED;
            }
            
            rotateLeft(root -> left);
        }
        else {
            leftChild -> balance = Node::BALANCED;
            root -> balance = Node::BALANCED;
        }
        
        rotateRight(root);
    }
    
    void rebalanceRight(Node*& root) {
        Node* rightChild = root -> right ? root -> right : NULL;
        
        if (rightChild && rightChild -> balance == Node::LEFT_HEAVY) {
            Node* rightLeftChild = rightChild -> left ? rightChild -> left : NULL;
            
            if (rightLeftChild && rightLeftChild -> balance == Node::RIGHT_HEAVY) {
                rightChild -> balance = Node::BALANCED;
                rightLeftChild -> balance = Node::BALANCED;
                root -> balance = Node::LEFT_HEAVY;
            }
            else if (rightLeftChild && rightLeftChild -> balance == Node::BALANCED) {
                rightChild -> balance = Node::BALANCED;
                rightLeftChild -> balance = Node::BALANCED;
                root -> balance = Node::BALANCED;
            }
            else if (rightLeftChild){
                rightChild -> balance = Node::RIGHT_HEAVY;
                rightLeftChild -> balance = Node::BALANCED;
                root -> balance = Node::BALANCED;
            }
            
            rotateRight(root -> right);
        }
        else {
            rightChild -> balance = Node::BALANCED;
            root -> balance = Node::BALANCED;
        }
        
        rotateLeft(root);
    }
    
    /** Return true if node removed from BST, else false */
    virtual bool removeNode(const T& data) {
        bool ret = remove(data, root);
        balanceTree();
        
        return ret;
    }
    
    /** Return true if BST cleared of all nodes, else false */
    virtual bool clearTree() {
        return resetTree(root);
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
        }
        while (outLevel(root, level, out));
        
        return out.str();
    }
    
    /** Call toString when class is used with output stream */
    friend std::ostream& operator<<(std::ostream& out, AVL &obj) {
        out << obj.toString();
        return out;
    }
    
    size_t getHeight(const T& data) const {
        return height(root, data);
    }
    
    void copyData(Node*& newRoot, Node* root) {
        if (root == NULL) return;
        insert(newRoot, root -> data);
        
        if (root -> left) copyData(newRoot, root -> left);
        if (root -> right) copyData(newRoot, root -> right);
    }
    
    void balanceTree() {
        if (root) {
            Node* newRoot = new Node(root -> data);
            if (root -> left) copyData(newRoot -> left, root -> left);
            if (root -> right) copyData(newRoot -> right, root -> right);
            delete root;
            
            root = newRoot;
        }
    }
    
    void replaceParent(Node*& oldNode, Node*& node) {
        if (node -> right != NULL) {
            replaceParent(oldNode, node -> right);
        }
        else {
            std::cout << "OTHER" << std::endl;
            oldNode -> data = node -> data;
            oldNode = node;
            node = node -> left;
        }
    }
};

/** Recursive function to remove called by removeNode() (Outside class since >10 lines) */
template<typename T>
bool AVL<T>::remove(const T& data, Node*& node) {
    if (node == NULL) return false;
    else if (data < node -> data) return remove(data, node -> left);
    else if (data > node -> data) return remove(data, node -> right);
    else if (node -> left == NULL && node -> right == NULL) {
        node = NULL;
        size--;
        return true;
    }
    else if (node -> right == NULL && node -> left != NULL) {
        node = node -> left;
        return true;
    }
    else if (node -> left == NULL && node -> right != NULL) {
        node = node -> right;
        return true;
    }
    else {
        Node* oldNode = node;
        if (node -> left == NULL) node = node -> right;
        else if (root -> right == NULL) node = node -> right;
        else {
            replaceParent(oldNode, oldNode -> left);
        }
        delete oldNode;
        size--;
        return true;
    }
    return false;
}

/** Output nodes at a given level (Outside class since >10 lines) */
template<typename T>
bool AVL<T>::outLevel(Node* node, int level, std::ostream& out) const {
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
bool AVL<T>::add(const T& data, Node*& node) {
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

