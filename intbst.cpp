// intbst.cpp
// Implements class IntBST


#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() {
    root = NULL;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) return false;

    if (value < n->info) {
        if (!n->left) {
            n->left = new Node(value);
            n->left->parent = n;        // maintain parent pointer
            return true;
        }
        return insert(value, n->left);
    }
    else {
        if (!n->right) {
            n->right = new Node(value);
            n->right->parent = n;       // maintain parent pointer
            return true;
        }
        return insert(value, n->right);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (!n) return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}
void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

int IntBST::count(Node *n) const {
    if (!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

// returns the node for a given value or NULL if none exists
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (!n) return NULL;
    if (n->info == value) return n;
    if (value < n->info) return getNodeFor(value, n->left);
    return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != NULL;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const {
    Node* target = getNodeFor(value, root);
    if (!target) return NULL;

    
    if (target->left) {
        Node* curr = target->left;
        while (curr->right) curr = curr->right;
        return curr;
    }

    
    Node* curr = target;
    while (curr->parent && curr->parent->left == curr) {
        curr = curr->parent;
    }
    return curr->parent;  
}


// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
    Node* p = getPredecessorNode(value);
    if (!p) return 0;
    return p->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* target = getNodeFor(value, root);
    if (!target) return NULL;

    
    if (target->right) {
        Node* curr = target->right;
        while (curr->left) curr = curr->left;
        return curr;
    }

    
    Node* curr = target;
    while (curr->parent && curr->parent->right == curr) {
        curr = curr->parent;
    }
    return curr->parent;  
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
    Node* s = getSuccessorNode(value);
    if (!s) return 0;
    return s->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node existed and was deleted, or false if not
bool IntBST::remove(int value) {
    Node* target = getNodeFor(value, root);
    if (!target) return false;

    
    if (target->left && target->right) {
        Node* succ = getSuccessorNode(value);
        target->info = succ->info;
        target = succ;  
    }

    
    Node* child = target->left ? target->left : target->right;

    if (child) child->parent = target->parent;

    if (!target->parent) {
        root = child;
    } else if (target->parent->left == target) {
        target->parent->left = child;
    } else {
        target->parent->right = child;
    }

    delete target;
    return true;
}