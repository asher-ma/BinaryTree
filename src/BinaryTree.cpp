#include "BinaryTreeAbstract.h"
#include "BinaryTree.h"
#include "NotFoundException.h"

// Constructors
template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(){}

template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(const ItemType& rootItem) {
    this->rootPtr = new BinaryNode<ItemType>(rootItem);
}

// BinaryTree(const ItemType& rootItem,
//         const BinaryTree<ItemType>* leftTreePtr,
//         const BinaryTree<ItemType>* rightTreePtr);

// BinaryTree(const BinaryNodeTree<ItemType>& tree);

// Destructor
template <typename ItemType>
BinaryTree<ItemType>::~BinaryTree() {}

// Members
// Returns true if tree is empty
template <typename ItemType>
bool BinaryTree<ItemType>::isEmpty() const {
    if (this->rootPtr == nullptr){
        return true;
    }
    return false;
}

// Returns height of tree
template <typename ItemType>
int BinaryTree<ItemType>::getHeight() const {
    return getHeightHelper(this->rootPtr);
}

// Finds height by recursing down each branch and returning length of longest path
template <typename ItemType>
int BinaryTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const {
    if (subTreePtr == nullptr){
        return 0;
    } else {
        return max(1+getHeightHelper(subTreePtr->getRightChildPtr()),
            1+getHeightHelper(subTreePtr->getLeftChildPtr()));
    }
}

// Returns number of nodes in tree
template <typename ItemType>
int BinaryTree<ItemType>::getNumberOfNodes() const {
    return getNumberOfNodesHelper(this->rootPtr);
}

// Finds number of nodes by recursing down each branch and summing length of each path
template <typename ItemType>
int BinaryTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const {
    if (subTreePtr == nullptr){
        return 0;
    } else {
        return 1+getNumberOfNodesHelper(subTreePtr->getRightChildPtr()) +
            getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    }
}

// Gets item stored in node
template <typename ItemType>
ItemType BinaryTree<ItemType>::getRootData() const {
    return this->rootPtr->getItem();
}

// Sets item stored in root node
template <typename ItemType>
void BinaryTree<ItemType>::setRootData( const ItemType& newData) {
    if (this->rootPtr == nullptr) {
        this->rootPtr = new BinaryNode<ItemType>(newData);
    } else {
        this->rootPtr->setItem(newData);
    }
}

template <typename ItemType>
bool BinaryTree<ItemType>::add( const ItemType& newData) {
    if (this->isEmpty()) {   // Case for if tree is empty
        this->rootPtr = new BinaryNode<ItemType>(newData);
        return true;
    } else {
        balancedAdd(this->rootPtr, new BinaryNode<ItemType>(newData));
        return true;
    }
}

template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
        BinaryNode<ItemType>* newNodePtr) {
    BinaryNode<ItemType>* leftChildPtr = subTreePtr->getLeftChildPtr();
    BinaryNode<ItemType>* rightChildPtr = subTreePtr->getRightChildPtr();
        
    if (leftChildPtr == nullptr) { 
        subTreePtr->setLeftChildPtr(newNodePtr);
        return subTreePtr;
    } else if (rightChildPtr == nullptr) {
        subTreePtr->setRightChildPtr(newNodePtr);
        return subTreePtr;
    }

    // If current node has two children traverse down the shorter path
    if (getHeightHelper(leftChildPtr) <= getHeightHelper(rightChildPtr)) {
        return balancedAdd(leftChildPtr, newNodePtr);
    } else {
        return balancedAdd(rightChildPtr, newNodePtr);
    }
}

// Pure virtual method placeholders (to avoid compilation errors):

template <typename ItemType>
bool BinaryTree<ItemType>::remove( const ItemType& data) {
    return false;
}

template <typename ItemType>
void BinaryTree<ItemType>::clear() {}

// Preorder traversal through tree until target is found
// template <typename ItemType>
// BinaryNode<ItemType>* BinaryTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const ;


// ERR: This is getEntry() for a BST not a general binary tree
//      The general binary tree getEntry() must check every node
// Finds and returns searched value if found in tree
template <typename ItemType>
ItemType BinaryTree<ItemType>::getEntry( const ItemType& anEntry) const {
    BinaryNode<ItemType>* current = this->rootPtr;

    while (current != nullptr) {
        if (anEntry == current->getItem()) {
            return current->getItem();
        } else if (anEntry < current->getItem()){
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    throw NotFoundExcep("Entry not found in tree");
}

// ERR: This is contains() for a BST not a general binary tree
//      The general binary tree contains() must check every node
// Returns true if tree contains searched entry, otherwise false
template <typename ItemType>
bool BinaryTree<ItemType>::contains( const ItemType& anEntry) const {
    BinaryNode<ItemType>* current = this->rootPtr;

    while (current != nullptr) {
        if (anEntry == current->getItem()) {
            return true;
        } else if (anEntry < current->getItem()){
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    return false;
}
// Traversals
// preorder: root, left, right
template <typename ItemType>
void BinaryTree<ItemType>::preorderTraverse( void visit(ItemType&)) const {
    preorder(visit, this->rootPtr);
}

template<typename ItemType>
void BinaryTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        ItemType item = treePtr->getItem();
        visit(item);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}


// inorder: left, root, right
template <typename ItemType>
void BinaryTree<ItemType>::inorderTraverse( void visit(ItemType&)) const {}

// template<typename ItemType>
// void BinaryTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const ;


// postorder: left, right, root
template <typename ItemType>
void BinaryTree<ItemType>::postorderTraverse( void visit(ItemType&)) const {}

// template<typename ItemType>
// void BinaryTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const ;
