#include "BinaryTreeAbstract.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "NotFoundException.h"

// Constructors


// Protected member functions
template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode) {
    if (subTreePtr == nullptr) {
        return newNode;
    } else if (subTreePtr->getItem() > newNode->getItem()) {
        tempPtr = insertInOrder(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    } else {
        tempPtr = insertInOrder(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success) {
    if (subTreePtr == nullptr) {
        success = false;
        return nullptr;
    } else if (subTreePtr->getItem() == target) {
        subTreePtr = removeNode(subTreePtr); // Remove the item
        success = true;
        return subTreePtr;
    } else if (subTreePtr->getItem() > target) {
        // Search the left subtree
        tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    } else {
        // Search the right subtree
        tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
        return subTreePtr;
    }
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr) {}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor) {}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const {}


// Public member functions

template <typename ItemType>
bool BinarySearchTree<ItemType>::add( const ItemType& newEntry) {}

template <typename ItemType>
bool BinarySearchTree<ItemType>::remove( const ItemType& anEntry) {}

template <typename ItemType>
void BinarySearchTree<ItemType>::setRootData( const ItemType& newData) const {}

/*
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

template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr) {
    if (subTreePtr->isLeaf()){
        delete subTreePtr;
        subTreePtr = nullPtr;
        return subTreePtr;
    }
    BinaryNode<ItemType>* leftChildPtr = subTreePtr->getLeftChildPtr();
    BinaryNode<ItemType>* rightChildPtr = subTreePtr->getRightChildPtr();
    if (leftChildPtr != nullptr && rightChildPtr == nullptr) { // Subtree only has left child
        nodeToConnectPtr = leftChildPtr;
    } else if (leftChildPtr == nullptr && rightChildPtr != nullptr) { // Subtree only has right child
        nodeToConnectPtr = rightChildPtr;
    } else {    // Subtree has two children
        BinaryNode<ItemType>* tempPtr = remove
    }

}

*/