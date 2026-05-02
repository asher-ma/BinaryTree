#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "BinaryNode.h"
#include "BinaryTreeAbstract.h"
#include "PrecondViolatedException.h"
#include "NotFoundException.h"

template < class ItemType>
class BinaryTree : public BinaryTreeAbstract<ItemType>{

    protected :
        int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const ;
        int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const ;
        void destroyTree(BinaryNode<ItemType>* subTreePtr);

        BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr,
        BinaryNode<ItemType>* newNodePtr);


        BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
        const ItemType target, bool& success);
        BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);

        BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target,
        bool& success) const ;
        BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const ;
        
        void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const ;
        void inorder(void visit(ItemType&),  BinaryNode<ItemType>* treePtr) const ;
        void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const ;

    public :    
        BinaryTree();
        BinaryTree(const ItemType& rootItem);
        BinaryTree(const ItemType& rootItem,
        const BinaryTree<ItemType>* leftTreePtr,
        const BinaryTree<ItemType>* rightTreePtr);
        BinaryTree(const BinaryTree<ItemType>& tree);
        virtual ~BinaryTree();
    
        bool isEmpty() const ;
        int getHeight() const ;
        int getNumberOfNodes() const ;
        ItemType getRootData() const ; // throw (PrecondViolatedExcep);
        void setRootData(const ItemType& newData);
        bool add(const ItemType& newData); // Adds a node
        bool remove(const ItemType& data); // Removes node containing given data
        void clear();

        ItemType getEntry(const ItemType& anEntry) const; // throw (NotFoundException);
        bool contains(const ItemType& anEntry) const ;
        
        void preorderTraverse(void visit(ItemType&)) const ;
        void inorderTraverse(void visit(ItemType&)) const ;
        void postorderTraverse(void visit(ItemType&)) const ;
        
        BinaryTree& operator=(const BinaryTree& rightHandSide);
}; // end BinaryTree

#include "../src/BinaryTree.cpp"

#endif