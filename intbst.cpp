// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

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
    if (!root){
        root = new Node(value);
        return true; 
    }
    return insert(value, root); 
    
    
    
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) return false;
    
    if (value < n->info){
        if (!n->left){
            n->left = new Node(value);
            return true; 
        }
        else{
            return insert(value, n->left); 
        }
    }
    else{
        if (!n->right){
            n->right = new Node(value);
            return true;
        }
        else{
            return insert(value, n->right);
        }
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
    int s = 0; 
    if (!n) return 0;
    
    s+= n->info;
    s+= sum(n->left);
    s+= sum(n->right); 

    return s; 
    
}

// return count of values
int IntBST::count() const {
    return count(root); 
}

int IntBST::count(Node *n) const {
    int c = 0; 

    if (!n){
        return 0; 
    }
    
    c+= 1 + count(n->left) + count(n->right);
    
    return c; 
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return NULL; 
    
    if (n->info == value) return n;
    
    
    if (n->info > value){
        return getNodeFor(value, n->left);

    }else{
        return getNodeFor(value, n->right); 
 
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    
    if (getNodeFor(value, root) != NULL){
        return true;
    }
    return false; 
    
}
    
    
    
    
    




// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    return getPredecessorNode(value, root);
}
IntBST::Node* IntBST::getPredecessorNode(int value, Node* n) const{
    if (!n){
        return NULL; 
    }
    
    if (value < n->info){
        n->left = getPredecessorNode(value, n->left)
    }
    else{
        n->right = getPredecessorNode(value, n->right)
    }
    
    return n; 
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    
    Node* target = getTargetNode(value, root);
    if (!target) return 0;
    
    return findPredecessor(target);
        
    }


int IntBST::findPredecessor(Node* target) const{
    if (target->left){
        return getLargest(target->left); 
    }
    else if (target->parent){
        if (target->parent->info < target->info){
            return target->parent->info;
        }
        else{
            Node* curr = target;
            while (curr->parent && curr->parent->info > target->info){
                curr = curr->parent; 
            }
            if (curr->parent) return curr->parent->info;
            return 0; 
        }
    }
    return 0; 
}
int IntBST::getLargest(Node* n) const {
    if (!n->right){
        return n->info; 
    }
    return getLargest(n->right); 
}

IntBST::Node* IntBST::getTargetNode(int value, Node* n) const{
    if (!n) return nullptr;
    if (value == n->info) return n;
    if (value < n->info) return getTargetNode(value, n->left);
    return getTargetNode(value, n->right); 
    
}



// returns the Node containing the successor of the given value


IntBST::Node* IntBST::getSuccessorNode(int value) const{
    if (!root) return NULL;
    
    Node* valNode = getTargetNode(value, root);
    Node* curr = valNode; 
    
    if (!curr) return NULL;
    
    if (curr->right){
        curr = curr->right;
        while (curr->left){
            curr = curr->left; 
        }
        return curr; 
    }
    
    if (!curr->right){
        if (curr->parent){
            while (valNode->info > curr->parent->info){
               curr = curr->parent;
            }
            return curr->parent;
        }
        
        if (valNode->info <= curr->parent->info){
            return curr->parent; 
        }
    
            
        
        else{
            return NULL; 
        }
    }
    
    
    
}






// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return -1; // REPLACE THIS NON-SOLUTION
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    return false; // REPLACE THIS NON-SOLUTION
}
