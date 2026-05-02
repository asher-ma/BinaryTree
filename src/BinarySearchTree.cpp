#include "BinaryTreeAbstract.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "NotFoundException.h"

// Constructors
template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : BinaryTree<ItemType>() {}

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) : BinaryTree<ItemType>(rootItem) {}

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree) : BinaryTree<ItemType>(tree) {}

template <typename ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {}


// Protected member functions
template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode) {
    if (subTreePtr == nullptr) {
        return newNode;
    }
    BinaryNode<ItemType>* tempPtr;
    BinaryNode<ItemType>* newNodePtr;
    if (subTreePtr->getItem() > newNode->getItem()) {
        tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    } else {
        tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success) {
    if (subTreePtr == nullptr) { // reached leaf
        success = false;
        return nullptr;
    } else if (subTreePtr->getItem() == target) { // reached target
        subTreePtr = removeNode(subTreePtr); // Remove the item
        success = true;
        return subTreePtr;
    }

    BinaryNode<ItemType>* tempPtr;
    if (subTreePtr->getItem() > target) {
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
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr) {
    BinaryNode<ItemType>* leftChildPtr = nodePtr->getLeftChildPtr();
    BinaryNode<ItemType>* rightChildPtr = nodePtr->getRightChildPtr();

    if (leftChildPtr == nullptr && rightChildPtr == nullptr) { // node is leaf
        // Remove leaf from the tree
        delete nodePtr;
        nodePtr = nullptr;
        return nodePtr;
    } else if ((leftChildPtr == nullptr) != (rightChildPtr == nullptr)) { // node only has one child
        BinaryNode<ItemType>* nodeToConnectPtr;
        if (leftChildPtr != nullptr) { // node only has left child
            nodeToConnectPtr = leftChildPtr;
        } else { // node only has right child
            nodeToConnectPtr = rightChildPtr;
        }
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    } else { // node has two children
        // Find the inorder successor of the entry in the left subtree rooted at nodes right child
        ItemType newNodeValue;
        BinaryNode<ItemType>* tempPtr;
        tempPtr = removeLeftmostNode(rightChildPtr, newNodeValue);
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(newNodeValue); // Put replacement value in node
        return nodePtr;
    }
}

// Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node.
// Returns a pointer to the revised subtree.
template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor) {
    if (subTreePtr->getLeftChildPtr() == nullptr) {
        // Deepest node on right child's left subtree with no left child
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    } else {
        return removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
    }

}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const {
    if (treePtr == nullptr) {
        return nullptr; // Not found
    } else if (treePtr->getItem() == target) {
        return treePtr; // Found
    } else if (treePtr->getItem() > target) {
        // Search left subtree
        return findNode(treePtr->getLeftChildPtr(), target);
    } else {
        // Search right subtree
        return findNode(treePtr->getRightChildPtr(), target);
    }
}


// Public member functions

template <typename ItemType>
bool BinarySearchTree<ItemType>::add( const ItemType& newEntry) {
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = insertInorder(this->rootPtr, newNodePtr);
    return true;
}

template <typename ItemType>
bool BinarySearchTree<ItemType>::remove( const ItemType& anEntry) {
    bool success = false;
    this->rootPtr = removeValue(this->rootPtr, anEntry, success);
    return success;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const {
    throw PrecondViolatedExcep("Cannot set root data on a BST");
}


// Reimplemented to use BST findNode()

template <typename ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const {
    return findNode(this->rootPtr, anEntry) != nullptr;
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const {
    BinaryNode<ItemType>* node = findNode(this->rootPtr, anEntry);
    if (node == nullptr) {
        throw NotFoundExcep("Entry not found in tree");
    }
    return node->getItem();
}