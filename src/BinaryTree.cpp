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

// Sets node item to provided data
template <typename ItemType>
void BinaryTree<ItemType>::setRootData( const ItemType& newData) {
    this->rootPtr->setItem(newData);
}

// Pure virtual method placeholders (to avoid compilation errors):
// TODO: Implement these
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

template <typename ItemType>
bool BinaryTree<ItemType>::remove( const ItemType& data) {
    return false;
}

template <typename ItemType>
void BinaryTree<ItemType>::clear() {}

// Traverse down each branch until target is found
// If every node has been checked then return nullptr
template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const {
    if (treePtr == nullptr) {
        return nullptr;
    }
    if (treePtr->getItem() == target) {
        return treePtr;
    }
    if (treePtr->getLeftChildPtr() != nullptr) {
        BinaryNode<ItemType>* node = findNode(treePtr->getLeftChildPtr(), target);
        if (node != nullptr) {
            return node;
        }
    }
    if (treePtr->getRightChildPtr() != nullptr) {
        BinaryNode<ItemType>* node = findNode(treePtr->getRightChildPtr(), target);
        if (node != nullptr) {
            return node;
        }
    }
    return nullptr;
}


// Finds and returns searched value if found in tree
template <typename ItemType>
ItemType BinaryTree<ItemType>::getEntry( const ItemType& anEntry) const {
    BinaryNode<ItemType>* node = findNode(this->rootPtr, anEntry);

    if (node != nullptr) {
        return node->getItem();
    } else {
        throw NotFoundExcep("Entry not found in tree");
    }
}

// Returns true if tree contains searched entry, otherwise false
template <typename ItemType>
bool BinaryTree<ItemType>::contains( const ItemType& anEntry) const {
    if (findNode(this->rootPtr, anEntry) != nullptr) {
        return true;
    } else {
        return false;
    }
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
void BinaryTree<ItemType>::inorderTraverse( void visit(ItemType&)) const {
    inorder(visit, this->rootPtr);
}

template<typename ItemType>
void BinaryTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        preorder(visit, treePtr->getLeftChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
        preorder(visit, treePtr->getRightChildPtr());
    }
}

// postorder: left, right, root
template <typename ItemType>
void BinaryTree<ItemType>::postorderTraverse( void visit(ItemType&)) const {
    postorder(visit, this->rootPtr);
}

template<typename ItemType>
void BinaryTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
    }
}