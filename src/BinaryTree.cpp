#include "BinaryTree.h"


// Constructors
template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(){}

template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(const ItemType& rootItem) {
    rootPtr = new BinaryNode<ItemType>(rootItem);
}

// BinaryTree(const ItemType& rootItem,
//         const BinaryTree<ItemType>* leftTreePtr,
//         const BinaryTree<ItemType>* rightTreePtr);

// BinaryTree(const BinaryNodeTree<ItemType>& tree);


// Members
template <typename ItemType>
bool isEmpty(){
    if (rootPtr == nullptr){
        return true;
    }
    return false;
}

template <typename ItemType>
int getHeight(){
    return getHeightHelper(rootPtr);
}

template <typename ItemType>
int getHeightHelper(BinaryNode<ItemType>* subTreePtr) {
    if (!subTreePtr.isEmpty()){
        return 0;
    } else {
        return max(1+getHeightHelper(subTreePtr->rightChildPtr),
            1+getHeightHelper(subTreePtr->leftChildPtr));
    }
}