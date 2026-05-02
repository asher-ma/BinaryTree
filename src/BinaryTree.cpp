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

// Combines two given subtrees under given root
template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(const ItemType& rootItem,
        const BinaryTree<ItemType>* leftTreePtr, const BinaryTree<ItemType>* rightTreePtr) {
    this->rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr), copyTree(rightTreePtr));
}

// Copy constructor
template <typename ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree<ItemType>& tree) {
    this->rootPtr = copyTree(tree.rootPtr);
}

// Destructor
template <typename ItemType>
BinaryTree<ItemType>::~BinaryTree() {}


// Protected memeber functions

// Copies tree by recursively copying its subtrees
// Returns pointer to new copy of tree
template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const {
    BinaryNode<ItemType>* newTreePtr = nullptr;

    if (treePtr != nullptr) {
        // Copy node
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
        
        // Recursively copy branches
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }

    return newTreePtr;
}

// Searches tree for a node containing target, removes it by pulling values
// up from longest path
// Returns the edited subtree
// Sets success to true if the target was found and removed, false otherwise
template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
        const ItemType target, bool& success) {
    if (subTreePtr == nullptr) {
        success = false;
        return nullptr;
    }

    if (subTreePtr->getItem() == target) {
        success = true;
        // Replace this node's value by pulling up from below, then delete the bottom leaf
        subTreePtr = moveValuesUpTree(subTreePtr);
        return subTreePtr;
    }

    // Recurse left, update left child pointer with result
    subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
    if (success) {
        return subTreePtr;
    }
    // Recurse right, update right child pointer with result
    subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
    return subTreePtr;
}

// Removes a node from the tree by overwriting its value with the value of its
// child along the longest path, recursing down until a leaf is reached and deleted.
// Returns the modified subtree pointer
template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr) {
    if (subTreePtr->isLeaf()) {
        delete subTreePtr;
        return nullptr;
    }

    BinaryNode<ItemType>* leftChildPtr = subTreePtr->getLeftChildPtr();
    BinaryNode<ItemType>* rightChildPtr = subTreePtr->getRightChildPtr();

    // Traverse down the longer path (or right if equal)
    if (getHeightHelper(leftChildPtr) <= getHeightHelper(rightChildPtr)) {
        subTreePtr->setItem(rightChildPtr->getItem());
        subTreePtr->setRightChildPtr(moveValuesUpTree(rightChildPtr));
    } else {
        subTreePtr->setItem(leftChildPtr->getItem());
        subTreePtr->setLeftChildPtr(moveValuesUpTree(leftChildPtr));
    }

    return subTreePtr;
}


// Public member functions

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

// Adds node to tree with given data
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
bool BinaryTree<ItemType>::remove(const ItemType& data) {
    bool success = false;
    this->rootPtr = removeValue(this->rootPtr, data, success);
    return success;
}

//TODO
template <typename ItemType>
void BinaryTree<ItemType>::clear() {}

// Traverse down each branch until target is found
// If every node has been checked then return nullptr
template <typename ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const {
    if (treePtr == nullptr) {
        success = false;
        return nullptr;
    }
    if (treePtr->getItem() == target) {
        return treePtr;
        success = true;
    }
    
    BinaryNode<ItemType>* node = findNode(treePtr->getLeftChildPtr(), target, success);
    if (node != nullptr) {
        return node;
    }
    return findNode(treePtr->getRightChildPtr(), target, success);
}


// Finds and returns searched value if found in tree
template <typename ItemType>
ItemType BinaryTree<ItemType>::getEntry( const ItemType& anEntry) const {
    bool success = false;
    BinaryNode<ItemType>* node = findNode(this->rootPtr, anEntry, success);

    if (success) {
        return node->getItem();
    } else {
        throw NotFoundExcep("Entry not found in tree");
    }
}

// Returns true if tree contains searched entry, otherwise false
template <typename ItemType>
bool BinaryTree<ItemType>::contains( const ItemType& anEntry) const {
    bool success = false;
    findNode(this->rootPtr, anEntry, success);
    return success;
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
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
        inorder(visit, treePtr->getRightChildPtr());
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
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
    }
}